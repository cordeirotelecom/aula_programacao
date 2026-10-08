/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  11 - Deep sleep
  Objetivo: dormir 10 segundos gastando muito pouca energia e acordar sozinho.
  Ligacao: nenhuma.
  Ao acordar, o ESP32 reinicia o programa do zero (setup roda de novo).
  RTC_DATA_ATTR guarda uma variavel na memoria RTC, que sobrevive ao sono.
*/

RTC_DATA_ATTR int contadorBoots = 0;

const uint64_t SEGUNDOS_DE_SONO = 10;

void setup() {
  Serial.begin(115200);
  delay(1000);
  contadorBoots++;
  Serial.print("Acordei! Boot numero ");
  Serial.println(contadorBoots);

  esp_sleep_enable_timer_wakeup(SEGUNDOS_DE_SONO * 1000000ULL);  // em microssegundos
  Serial.println("Dormindo por 10 segundos...");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {
  // nunca chega aqui: o ESP32 dorme no fim do setup()
}

/*
  EXERCICIOS
  1) Mude o tempo de sono para 30 segundos.
  2) Pisque um LED por 1 segundo antes de dormir.
  3) Descubra o motivo do despertar com esp_sleep_get_wakeup_cause().
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
