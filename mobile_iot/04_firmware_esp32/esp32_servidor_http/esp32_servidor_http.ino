/* Elaborado pelo Prof. Vagner Cordeiro */
/* esp32_servidor_http - API HTTP no ESP32 para o app mobile (PWA)
 *
 * O que faz:
 *   GET /dados            -> {"temperatura":27.5,"umidade":61,"led":false}
 *   GET /led?estado=1     -> liga o LED  e responde {"led":true}
 *   GET /led?estado=0     -> desliga     e responde {"led":false}
 *
 * Como usar:
 *   1. Arduino IDE > Placa: ESP32 (instale "esp32 by Espressif" no Gerenciador de Placas)
 *   2. Troque SSID e SENHA abaixo pelos do seu Wi-Fi (2,4 GHz)
 *   3. Envie para a placa, abra o Monitor Serial (115200) e anote o IP
 *   4. No app, digite esse IP no campo "Endereco do dispositivo"
 *
 * Os sensores aqui sao SIMULADOS (valores gerados); troque por leituras reais
 * (DHT22, sensor de solo) quando tiver o hardware.
 */
#include <WiFi.h>
#include <WebServer.h>

const char *SSID = "SEU_WIFI";
const char *SENHA = "SUA_SENHA";
const int PINO_LED = 2;          /* LED da propria placa */

WebServer servidor(80);
bool ledLigado = false;

/* CORS: permite que a pagina do app (outro endereco) leia a resposta */
void liberarCors()
{
    servidor.sendHeader("Access-Control-Allow-Origin", "*");
}

void aoPedirDados()
{
    float temperatura = 26.0 + (millis() % 10000) / 2000.0;   /* simulado */
    int umidade = 40 + (millis() / 1000) % 40;                /* simulado */
    String json = "{\"temperatura\":" + String(temperatura, 1) +
                  ",\"umidade\":" + String(umidade) +
                  ",\"led\":" + (ledLigado ? "true" : "false") + "}";
    liberarCors();
    servidor.send(200, "application/json", json);
}

void aoPedirLed()
{
    if (!servidor.hasArg("estado")) {
        liberarCors();
        servidor.send(400, "application/json", "{\"erro\":\"faltou estado\"}");
        return;
    }
    ledLigado = servidor.arg("estado") == "1";
    digitalWrite(PINO_LED, ledLigado ? HIGH : LOW);
    liberarCors();
    servidor.send(200, "application/json", String("{\"led\":") + (ledLigado ? "true" : "false") + "}");
}

void setup()
{
    Serial.begin(115200);
    pinMode(PINO_LED, OUTPUT);

    WiFi.begin(SSID, SENHA);
    Serial.print("Conectando");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Conectado! IP do dispositivo: ");
    Serial.println(WiFi.localIP());

    servidor.on("/dados", aoPedirDados);
    servidor.on("/led", aoPedirLed);
    servidor.begin();
}

void loop()
{
    servidor.handleClient();   /* atende os pedidos do celular */
}

/* EXERCICIOS:
   1. Troque a temperatura simulada por uma leitura real (DHT22).
   2. Crie a rota /bomba que liga um rele em outro pino.
   3. Acrescente o campo "wifi" (WiFi.RSSI()) ao JSON.
*/
/* Executar: abra este arquivo na Arduino IDE (pasta e arquivo tem o mesmo nome), escolha a placa ESP32 e clique em Carregar */
