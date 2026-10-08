// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 06 - Monitor Serial
   Conceitos: Serial.begin, Serial.println e leitura de comandos digitados.
   Digite 1 para ligar o LED e 0 para desligar (Monitor Serial, 9600 baud). */

const int PINO_LED = 13;

void setup() {
  pinMode(PINO_LED, OUTPUT);
  Serial.begin(9600);                         // velocidade da comunicacao
  Serial.println("Digite 1 (liga) ou 0 (desliga)");
}

void loop() {
  if (Serial.available() > 0) {               // chegou algum caractere?
    char comando = Serial.read();
    if (comando == '1') {
      digitalWrite(PINO_LED, HIGH);
      Serial.println("LED ligado");
    } else if (comando == '0') {
      digitalWrite(PINO_LED, LOW);
      Serial.println("LED desligado");
    }
  }
}

/* EXERCICIOS: 1) Adicione o comando 'p' para piscar 3 vezes.
   2) Responda "comando invalido" para outras teclas.
   COMO EXECUTAR: abra no Arduino IDE, clique em Carregar e depois em
   Ferramentas > Monitor Serial (9600 baud). Ou use https://wokwi.com. */
