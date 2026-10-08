/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  02 - Piscar LED
  Objetivo: ligar e desligar um LED a cada meio segundo.
  Ligacao: GPIO 2 -> resistor 220 ohm -> LED (perna longa) ; perna curta -> GND.
  ATENCAO: a placa pode ter LED proprio em outro pino. Confira a sua placa e,
  se preferir, use um LED externo com resistor de 220 ohm.
*/

#if CONFIG_IDF_TARGET_ESP32S3
const int PINO_LED = 2;  // ESP32-S3
#else
const int PINO_LED = 2;  // ESP32 classico
#endif

void setup() {
  pinMode(PINO_LED, OUTPUT);  // pino como saida
}

void loop() {
  digitalWrite(PINO_LED, HIGH);  // liga
  delay(500);
  digitalWrite(PINO_LED, LOW);   // desliga
  delay(500);
}

/*
  EXERCICIOS
  1) Faca o LED piscar rapido (100 ms) e depois lento (1000 ms).
  2) Faca o padrao SOS (3 curtos, 3 longos, 3 curtos).
  3) Ligue um segundo LED em outro pino seguro (ex.: GPIO 4) e alterne os dois.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
