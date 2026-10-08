// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 02 - Botao controla LED
   Circuito: LED + resistor 220 ohm no pino 8; botao entre pino 2 e GND.
   Conceitos: digitalRead, INPUT_PULLUP (resistor interno: botao solto = HIGH,
   pressionado = LOW). */

const int PINO_BOTAO = 2;
const int PINO_LED = 8;

void setup() {
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  if (digitalRead(PINO_BOTAO) == LOW) {   // pressionado
    digitalWrite(PINO_LED, HIGH);
  } else {
    digitalWrite(PINO_LED, LOW);
  }
}

/* EXERCICIOS: 1) Inverta: LED acende ao soltar. 2) Faca o botao alternar
   (liga/desliga) o LED a cada clique.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com (Arduino Uno + LED + botao). */
