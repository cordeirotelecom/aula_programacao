// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 05 - Potenciometro controla o brilho
   Circuito: potenciometro com extremos em 5V e GND e o pino do meio em A0;
   LED + resistor 220 ohm no pino 9.
   Conceitos: analogRead (0 a 1023), map (muda de escala). */

const int PINO_POT = A0;
const int PINO_LED = 9;

void setup() {
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  int leitura = analogRead(PINO_POT);          // 0 a 1023
  int brilho = map(leitura, 0, 1023, 0, 255);  // converte para 0 a 255
  analogWrite(PINO_LED, brilho);
}

/* EXERCICIOS: 1) Mostre a leitura no Monitor Serial. 2) Use o
   potenciometro para controlar a velocidade de um LED piscando.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com (adicione um potenciometro). */
