// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 08 - Sensor de temperatura LM35
   Circuito: LM35 com pinos 5V, saida em A0 e GND.
   O LM35 gera 10 mV por grau Celsius.
   Conta: tensao = leitura * 5.0 / 1023; temperatura = tensao * 100. */

const int PINO_LM35 = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int leitura = analogRead(PINO_LM35);
  float tensao = leitura * 5.0 / 1023.0;
  float temperatura = tensao * 100.0;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");
  delay(1000);
}

/* EXERCICIOS: 1) Acenda um LED se passar de 30 C. 2) Calcule a media
   de 10 leituras para estabilizar o valor.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar (Monitor
   Serial a 9600 baud). No Wokwi use o sensor NTC (valores diferentes). */
