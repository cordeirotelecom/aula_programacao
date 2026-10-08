// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 07 - Sensor de luz (LDR)
   Circuito: LDR entre 5V e A0; resistor de 10 kohm entre A0 e GND;
   LED + resistor 220 ohm no pino 8.
   O LED acende quando fica escuro (leitura baixa). */

const int PINO_LDR = A0;
const int PINO_LED = 8;
const int LIMITE_ESCURO = 400;     // ajuste conforme o ambiente

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int luz = analogRead(PINO_LDR);
  Serial.print("Luz: ");
  Serial.println(luz);

  if (luz < LIMITE_ESCURO) {
    digitalWrite(PINO_LED, HIGH);  // escuro: acende
  } else {
    digitalWrite(PINO_LED, LOW);
  }
  delay(200);
}

/* EXERCICIOS: 1) Ajuste LIMITE_ESCURO ao seu ambiente. 2) Use PWM para
   que o LED fique mais forte quanto mais escuro.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar (Monitor
   Serial a 9600 baud), ou simule em https://wokwi.com. */
