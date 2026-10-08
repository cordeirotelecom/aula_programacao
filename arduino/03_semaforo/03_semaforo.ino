// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 03 - Semaforo
   Circuito: LED vermelho no pino 10, amarelo no 9, verde no 8
   (cada um com resistor de 220 ohm ate o GND).
   Conceitos: varias saidas e sequencia de tempos. */

const int VERMELHO = 10;
const int AMARELO = 9;
const int VERDE = 8;

void setup() {
  pinMode(VERMELHO, OUTPUT);
  pinMode(AMARELO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void acender(int pino, int tempo_ms) {
  digitalWrite(VERMELHO, LOW);
  digitalWrite(AMARELO, LOW);
  digitalWrite(VERDE, LOW);
  digitalWrite(pino, HIGH);         // so o pino escolhido fica ligado
  delay(tempo_ms);
}

void loop() {
  acender(VERDE, 4000);
  acender(AMARELO, 1500);
  acender(VERMELHO, 4000);
}

/* EXERCICIOS: 1) Adicione um semaforo de pedestres. 2) Faca o amarelo
   piscar 3 vezes antes de ir para o vermelho.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com. */
