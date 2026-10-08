/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  PROJETO 2 - Painel web em modo Access Point (AP)

  OBJETIVO
    O proprio ESP32 cria uma rede WiFi (nao precisa de roteador). Voce conecta o
    celular nela e le dados (simulados) e liga/desliga um LED.
    Compativel com o app da pasta mobile_iot do curso.

  MATERIAIS
    ESP32 ou ESP32-S3, 1 LED, 1 resistor 220 ohm, jumpers.

  LIGACAO
    GPIO 2 -> 220 ohm -> LED -> GND (confira o LED da sua placa; use LED externo)

  PASSO A PASSO
    1) Carregue o codigo. 2) No celular, conecte na rede "ESP32-Painel"
       (senha 12345678). 3) Abra no navegador http://192.168.4.1/dados
    4) Para o LED: http://192.168.4.1/led?estado=1 (liga) e ?estado=0 (desliga).

  COMO TESTAR
    /dados devolve JSON: {"temperatura":25.3,"umidade":60.1,"led":false}
    As rotas enviam o cabecalho Access-Control-Allow-Origin: * para que uma
    pagina/app em outro endereco consiga ler os dados.
    Obs.: o celular pode avisar "sem internet" na rede do ESP32; mantenha conectado.
*/
#include <WiFi.h>
#include <WebServer.h>

const char* NOME_REDE = "ESP32-Painel";
const char* SENHA_REDE = "12345678";  // minimo 8 caracteres
const int PINO_LED = 2;

WebServer servidor(80);
bool ledLigado = false;

void liberarCors() {
  servidor.sendHeader("Access-Control-Allow-Origin", "*");
}

void rotaDados() {
  // sensores simulados: variam com o tempo
  float temperatura = 25.0 + (millis() / 1000 % 20) / 4.0;
  float umidade = 50.0 + (millis() / 1000 % 30);
  String json = "{\"temperatura\":" + String(temperatura, 1);
  json += ",\"umidade\":" + String(umidade, 1);
  json += ",\"led\":" + String(ledLigado ? "true" : "false") + "}";
  liberarCors();
  servidor.send(200, "application/json", json);
}

void rotaLed() {
  if (servidor.hasArg("estado")) {
    ledLigado = servidor.arg("estado") == "1";
    digitalWrite(PINO_LED, ledLigado ? HIGH : LOW);
  }
  liberarCors();
  servidor.send(200, "application/json", String("{\"led\":") + (ledLigado ? "true" : "false") + "}");
}

void rotaInicial() {
  liberarCors();
  servidor.send(200, "text/plain", "ESP32 Painel. Use /dados e /led?estado=1");
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  WiFi.softAP(NOME_REDE, SENHA_REDE);  // cria a rede
  Serial.print("Rede criada. IP do ESP32: ");
  Serial.println(WiFi.softAPIP());  // normalmente 192.168.4.1

  servidor.on("/", rotaInicial);
  servidor.on("/dados", rotaDados);
  servidor.on("/led", rotaLed);
  servidor.begin();
}

void loop() {
  servidor.handleClient();
}

/*
  EXERCICIOS
  1) Troque o nome e a senha da rede.
  2) Ligue um sensor real (potenciometro no ADC1) em vez da temperatura simulada.
  3) Adicione a rota /uptime com os segundos desde que ligou.
  4) Teste no app da pasta mobile_iot usando http://192.168.4.1 como endereco.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
