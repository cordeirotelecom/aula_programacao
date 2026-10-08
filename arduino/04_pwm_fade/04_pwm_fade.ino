// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 04 - PWM: LED com brilho suave (fade)
   Circuito: LED + resistor 220 ohm no pino 9 (pino com PWM, marcado com ~).
   Conceitos: analogWrite(pino, 0 a 255) simula tensao variavel. */

const int PINO_LED = 9;
int brilho = 0;
int passo = 5;

void setup() {
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  analogWrite(PINO_LED, brilho);
  brilho += passo;
  if (brilho <= 0 || brilho >= 255) {
    passo = -passo;                 // inverte a direcao nos extremos
  }
  delay(30);
}

/* EXERCICIOS: 1) Deixe o efeito mais lento. 2) Use dois LEDs, um
   acendendo enquanto o outro apaga.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com. */
