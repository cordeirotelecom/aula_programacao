/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  10 - Dois nucleos (FreeRTOS)
  Objetivo: rodar duas tarefas ao mesmo tempo, uma em cada nucleo.
  Ligacao: LED: GPIO 2 -> resistor 220 ohm -> LED -> GND.
  A tarefa 1 pisca o LED; a tarefa 2 escreve na serial. Uma nao trava a outra.
*/

const int PINO_LED = 2;

void tarefaPiscar(void* parametro) {
  pinMode(PINO_LED, OUTPUT);
  for (;;) {  // tarefa nunca termina
    digitalWrite(PINO_LED, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(PINO_LED, LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void tarefaSerial(void* parametro) {
  int n = 0;
  for (;;) {
    n++;
    Serial.print("Tarefa serial no nucleo ");
    Serial.print(xPortGetCoreID());
    Serial.print(" - contagem ");
    Serial.println(n);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  // funcao, nome, pilha, parametro, prioridade, handle, nucleo
  xTaskCreatePinnedToCore(tarefaPiscar, "Piscar", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(tarefaSerial, "Serial", 4096, NULL, 1, NULL, 1);
}

void loop() {
  // o loop() do Arduino tambem roda (no nucleo 1); aqui nao precisamos dele
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

/*
  EXERCICIOS
  1) Troque os nucleos (0 e 1) das tarefas e veja o que muda.
  2) Crie uma terceira tarefa que le o potenciometro.
  3) Pesquise: por que usar vTaskDelay em vez de delay dentro de tarefas?
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
