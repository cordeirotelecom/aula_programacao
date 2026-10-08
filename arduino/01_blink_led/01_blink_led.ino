// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 01 - Blink (piscar LED)
   Componentes: nenhum extra (usa o LED da propria placa, pino 13).
   Conceitos: setup(), loop(), pinMode, digitalWrite, delay. */

const int PINO_LED = LED_BUILTIN;   // LED da placa (pino 13 no Arduino Uno)

void setup() {
  pinMode(PINO_LED, OUTPUT);        // pino como saida
}

void loop() {
  digitalWrite(PINO_LED, HIGH);     // liga
  delay(1000);                      // espera 1 segundo
  digitalWrite(PINO_LED, LOW);      // desliga
  delay(1000);
}

/* EXERCICIOS: 1) Pisque mais rapido (200 ms). 2) Faca o padrao SOS.
   COMO EXECUTAR: abra este arquivo no Arduino IDE, escolha a placa
   (Ferramentas > Placa > Arduino Uno), a porta COM e clique em Carregar.
   Sem placa: cole o codigo em https://wokwi.com e clique em Play. */
