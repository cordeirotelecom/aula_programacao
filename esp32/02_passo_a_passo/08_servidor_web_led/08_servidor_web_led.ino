/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  08 - Servidor web para ligar/desligar o LED
  Objetivo: abrir uma pagina no celular/PC (mesma rede) com botoes Ligar e Desligar.
  Ligacao: GPIO 2 -> resistor 220 ohm -> LED -> GND (confira o LED da sua placa).
  Passos: troque SEU_WIFI/SUA_SENHA, carregue, veja o IP no Monitor Serial
  e digite o IP no navegador (ex.: http://192.168.0.50).
*/
#include <WiFi.h>
#include <WebServer.h>

const char* SEU_WIFI = "NOME_DA_REDE";
const char* SUA_SENHA = "SENHA_DA_REDE";
const int PINO_LED = 2;

WebServer servidor(80);  // servidor na porta 80
bool ledLigado = false;

void paginaInicial() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'></head><body>";
  html += "<h1>LED do ESP32</h1>";
  html += ledLigado ? "<p>Estado: LIGADO</p>" : "<p>Estado: DESLIGADO</p>";
  html += "<a href='/ligar'><button>Ligar</button></a> ";
  html += "<a href='/desligar'><button>Desligar</button></a>";
  html += "</body></html>";
  servidor.send(200, "text/html", html);
}

void ligar() {
  ledLigado = true;
  digitalWrite(PINO_LED, HIGH);
  servidor.sendHeader("Location", "/");  // volta para a pagina inicial
  servidor.send(303);
}

void desligar() {
  ledLigado = false;
  digitalWrite(PINO_LED, LOW);
  servidor.sendHeader("Location", "/");
  servidor.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  WiFi.begin(SEU_WIFI, SUA_SENHA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Abra no navegador: http://");
  Serial.println(WiFi.localIP());

  servidor.on("/", paginaInicial);
  servidor.on("/ligar", ligar);
  servidor.on("/desligar", desligar);
  servidor.begin();
}

void loop() {
  servidor.handleClient();  // atende os pedidos do navegador
}

/*
  EXERCICIOS
  1) Mude o titulo e as cores da pagina.
  2) Adicione um botao "Piscar" (rota /piscar).
  3) Mostre na pagina o tempo ligado (millis()).
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
