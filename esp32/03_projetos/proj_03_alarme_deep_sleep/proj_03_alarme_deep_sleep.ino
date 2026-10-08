/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  PROJETO 3 - Alarme com deep sleep e sensor PIR

  OBJETIVO
    O ESP32 dorme gastando quase nada e acorda quando o sensor de presenca (PIR)
    detecta movimento. Ao acordar, pisca um LED (alarme), conta quantas vezes
    disparou e volta a dormir.

  MATERIAIS
    ESP32 ou ESP32-S3, sensor PIR (HC-SR501), 1 LED, 1 resistor 220 ohm, jumpers.

  LIGACAO
    PIR: VCC -> 5V (pino VIN/5V da placa, o HC-SR501 e alimentado com 5V),
         GND -> GND, OUT -> pino do PIR (classico: GPIO 33; S3: GPIO 4).
    A saida do PIR e 3,3 V, segura para o ESP32. Se o seu modulo for 5 V na saida, use divisor de tensao.
    LED: GPIO 2 -> 220 ohm -> LED -> GND.
    O pino do PIR precisa ser um pino RTC (acorda o chip): classico 0,2,4,12-15,25-27,32-39;
    S3: GPIO 0 a 21.

  PASSO A PASSO
    1) Monte. 2) Carregue. 3) Espere ~30 s o PIR se estabilizar.
    4) Mova a mao na frente do sensor: o LED pisca e o contador aumenta.

  COMO TESTAR
    Monitor Serial 115200 mostra "Disparo numero N". O contador fica em
    RTC_DATA_ATTR, entao sobrevive ao sono (mas zera se desligar a energia).
*/

#if CONFIG_IDF_TARGET_ESP32S3
const int PINO_PIR = 4;
#else
const int PINO_PIR = 33;
#endif
const int PINO_LED = 2;

RTC_DATA_ATTR int disparos = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(PINO_LED, OUTPUT);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    disparos++;
    Serial.print("ALARME! Disparo numero ");
    Serial.println(disparos);
    for (int i = 0; i < 6; i++) {  // pisca 3 vezes
      digitalWrite(PINO_LED, !digitalRead(PINO_LED));
      delay(200);
    }
    digitalWrite(PINO_LED, LOW);
  } else {
    Serial.println("Primeira ligacao. Armando o alarme...");
  }

  // espera o PIR voltar a LOW, senao acordaria na hora
  pinMode(PINO_PIR, INPUT);
  while (digitalRead(PINO_PIR) == HIGH) {
    delay(100);
  }

  esp_sleep_enable_ext0_wakeup((gpio_num_t)PINO_PIR, 1);  // acorda com nivel 1
  Serial.println("Dormindo ate detectar movimento...");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
  // nunca executa
}

/*
  EXERCICIOS
  1) Troque o LED por um buzzer ativo.
  2) Alem do movimento, acorde sozinho a cada 60 s com esp_sleep_enable_timer_wakeup.
  3) Guarde o contador em Preferences para nao perder ao tirar a energia.
  4) Pesquise: quanta corrente o ESP32 gasta em deep sleep?
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
