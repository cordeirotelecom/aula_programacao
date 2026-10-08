/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  07 - Conectar ao WiFi
  Objetivo: conectar ao roteador e mostrar o endereco IP.
  Ligacao: nenhuma. Troque SEU_WIFI e SUA_SENHA pelos dados da sua rede 2,4 GHz
  (o ESP32 nao conecta em redes 5 GHz).
*/
#include <WiFi.h>

const char* SEU_WIFI = "NOME_DA_REDE";
const char* SUA_SENHA = "SENHA_DA_REDE";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA);  // modo estacao (cliente)
  WiFi.begin(SEU_WIFI, SUA_SENHA);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado! IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Sinal (RSSI): ");
  Serial.println(WiFi.RSSI());
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexao perdida, reconectando...");
    WiFi.reconnect();
  }
  delay(5000);
}

/*
  EXERCICIOS
  1) Errar a senha de proposito e observar o que acontece.
  2) Mostre o endereco MAC com WiFi.macAddress().
  3) Coloque um limite de 20 tentativas e avise se falhar.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
