// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 11 - Servo motor
   Circuito: fio marrom/preto em GND, vermelho em 5V, laranja/amarelo no pino 9.
   Conceitos: biblioteca Servo (ja vem no Arduino IDE), angulos de 0 a 180. */
#include <Servo.h>

Servo meuServo;
const int PINO_SERVO = 9;

void setup() {
  meuServo.attach(PINO_SERVO);
}

void loop() {
  for (int angulo = 0; angulo <= 180; angulo += 5) {
    meuServo.write(angulo);
    delay(30);
  }
  for (int angulo = 180; angulo >= 0; angulo -= 5) {
    meuServo.write(angulo);
    delay(30);
  }
}

/* EXERCICIOS: 1) Controle o angulo com um potenciometro (map 0-1023 para
   0-180). 2) Pare em 90 graus por 2 segundos a cada volta.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com (adicione um servo). */
