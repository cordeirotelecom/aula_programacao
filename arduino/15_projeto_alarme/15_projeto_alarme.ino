// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 15 - PROJETO FINAL: Alarme de presenca
   Junta o que foi aprendido: sensor ultrassonico, LED, buzzer, botao e Serial.
   Circuito: HC-SR04 (TRIG pino 9, ECHO pino 10); LED vermelho no pino 8;
   buzzer no pino 7; botao entre pino 2 e GND (liga/desliga o alarme).
   Funcionamento: com o alarme armado, se algo chegar a menos de 30 cm,
   o LED acende e o buzzer toca. */

const int PINO_TRIG = 9;
const int PINO_ECHO = 10;
const int PINO_LED = 8;
const int PINO_BUZZER = 7;
const int PINO_BOTAO = 2;
const float DISTANCIA_ALARME = 30.0;

bool armado = true;
bool botaoAnterior = HIGH;

float medirDistancia() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  long tempo = pulseIn(PINO_ECHO, HIGH, 30000);   // limite de espera 30 ms
  if (tempo == 0) {
    return 999.0;                                  // sem eco: nada por perto
  }
  return tempo * 0.034 / 2;
}

void setup() {
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Alarme armado");
}

void loop() {
  // clique no botao alterna armado/desarmado
  bool botao = digitalRead(PINO_BOTAO);
  if (botaoAnterior == HIGH && botao == LOW) {
    armado = !armado;
    Serial.println(armado ? "Alarme armado" : "Alarme desarmado");
  }
  botaoAnterior = botao;

  float distancia = medirDistancia();
  if (armado && distancia < DISTANCIA_ALARME) {
    digitalWrite(PINO_LED, HIGH);
    tone(PINO_BUZZER, 1000);
  } else {
    digitalWrite(PINO_LED, LOW);
    noTone(PINO_BUZZER);
  }
  delay(100);
}

/* EXERCICIOS: 1) Faca o LED piscar enquanto o alarme toca. 2) Grave na
   EEPROM quantas vezes o alarme disparou. 3) Ajuste DISTANCIA_ALARME.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar (Monitor
   Serial a 9600 baud), ou simule em https://wokwi.com. */
