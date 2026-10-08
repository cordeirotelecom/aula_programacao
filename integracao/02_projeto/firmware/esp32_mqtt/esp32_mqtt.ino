// Elaborado pelo Prof. Vagner Cordeiro
// ESP32 REAL: le temperatura/umidade (simuladas aqui), publica por MQTT e recebe comando do LED.
// Biblioteca necessaria: "PubSubClient" (Nick O'Leary) - Arduino IDE > Gerenciar Bibliotecas.
// Placa: ESP32 Dev Module (ou ESP32S3 Dev Module).
#include <WiFi.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "COLOQUE_SEU_WIFI";
const char* WIFI_SENHA = "COLOQUE_SUA_SENHA";
// IP do computador que roda o broker (use ipconfig no PowerShell)
const char* MQTT_SERVIDOR = "192.168.0.10";
const int MQTT_PORTA = 1883;
const char* DISPOSITIVO = "sala1";
const int PINO_LED = 2;

WiFiClient rede;
PubSubClient mqtt(rede);
bool ledLigado = false;
unsigned long ultimo = 0;
char topicoDados[48];
char topicoComando[48];

// Chamada quando chega mensagem no topico de comando: {"led":true}
void aoReceber(char* topico, byte* payload, unsigned int tamanho) {
  String texto;
  for (unsigned int i = 0; i < tamanho; i++) texto += (char)payload[i];
  if (texto.indexOf("true") >= 0) ledLigado = true;
  if (texto.indexOf("false") >= 0) ledLigado = false;
  digitalWrite(PINO_LED, ledLigado ? HIGH : LOW);
}

void conectarWifi() {
  WiFi.begin(WIFI_SSID, WIFI_SENHA);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nWiFi ok: " + WiFi.localIP().toString());
}

void conectarMqtt() {
  while (!mqtt.connected()) {
    if (mqtt.connect(DISPOSITIVO)) mqtt.subscribe(topicoComando);
    else delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  snprintf(topicoDados, sizeof(topicoDados), "estufa/%s/dados", DISPOSITIVO);
  snprintf(topicoComando, sizeof(topicoComando), "estufa/%s/comando", DISPOSITIVO);
  conectarWifi();
  mqtt.setServer(MQTT_SERVIDOR, MQTT_PORTA);
  mqtt.setCallback(aoReceber);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) conectarWifi();
  if (!mqtt.connected()) conectarMqtt();
  mqtt.loop();

  if (millis() - ultimo >= 2000) {
    ultimo = millis();
    // Troque por leitura de um sensor real (ex.: DHT22) quando tiver um
    float temperatura = 27.0 + 5.0 * sin(millis() / 20000.0);
    int umidade = 55 + (int)(20.0 * cos(millis() / 30000.0));
    char json[96];
    snprintf(json, sizeof(json), "{\"temperatura\":%.1f,\"umidade\":%d,\"led\":%s}",
             temperatura, umidade, ledLigado ? "true" : "false");
    mqtt.publish(topicoDados, json);
    Serial.println(json);
  }
}
// Executar: Arduino IDE > abrir este arquivo > editar WIFI e MQTT_SERVIDOR > Upload (seta ->)
