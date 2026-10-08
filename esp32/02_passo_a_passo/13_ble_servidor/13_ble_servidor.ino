/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  13 - BLE servidor
  Objetivo: o ESP32 vira um aparelho Bluetooth Low Energy que publica um numero
  (contador) lido pelo celular.
  Ligacao: nenhuma. No celular, instale o app "nRF Connect", procure
  "ESP32-Curso", conecte e toque na seta de leitura/notificacao da caracteristica.
  Funciona no ESP32 classico e no S3 (BLE; o S3 nao tem Bluetooth Classic).
  Use os UUIDs abaixo (podem ser trocados por outros gerados na internet).
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define UUID_SERVICO "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define UUID_CARACTERISTICA "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic* caracteristica;
int contador = 0;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32-Curso");  // nome que aparece no celular
  BLEServer* servidor = BLEDevice::createServer();
  BLEService* servico = servidor->createService(UUID_SERVICO);
  caracteristica = servico->createCharacteristic(
    UUID_CARACTERISTICA,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  caracteristica->setValue("0");
  servico->start();

  BLEAdvertising* anuncio = BLEDevice::getAdvertising();
  anuncio->addServiceUUID(UUID_SERVICO);
  BLEDevice::startAdvertising();  // comeca a "gritar" que existe
  Serial.println("BLE ativo: procure ESP32-Curso no celular");
}

void loop() {
  contador++;
  String texto = String(contador);
  caracteristica->setValue(texto.c_str());
  caracteristica->notify();  // avisa quem estiver conectado
  Serial.println(texto);
  delay(2000);
}

/*
  EXERCICIOS
  1) Mude o nome do dispositivo para "ESP32-<seu nome>".
  2) Publique a leitura do potenciometro em vez do contador.
  3) Pesquise: qual a diferenca entre READ, WRITE e NOTIFY?
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
