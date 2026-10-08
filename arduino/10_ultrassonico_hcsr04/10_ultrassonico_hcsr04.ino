// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 10 - Sensor ultrassonico HC-SR04 (medir distancia)
   Circuito: VCC em 5V, GND em GND, TRIG no pino 9 e ECHO no pino 10.
   Conta: o som viaja ~0,034 cm por microssegundo; o eco vai e volta,
   entao distancia = tempo * 0,034 / 2. */

const int PINO_TRIG = 9;
const int PINO_ECHO = 10;

void setup() {
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);    // pulso de 10 us dispara a medicao
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);

  long tempo = pulseIn(PINO_ECHO, HIGH);   // duracao do eco em us
  float distancia = tempo * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(300);
}

/* EXERCICIOS: 1) Acenda um LED quando a distancia for menor que 20 cm.
   2) Faca um sensor de estacionamento: buzzer mais rapido quanto mais perto.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar (Monitor
   Serial a 9600 baud), ou simule em https://wokwi.com (HC-SR04). */
