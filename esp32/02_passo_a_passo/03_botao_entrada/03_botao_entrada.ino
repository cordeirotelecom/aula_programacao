/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  03 - Botao como entrada
  Objetivo: acender o LED enquanto o botao estiver apertado.
  Ligacao: botao entre GPIO 15 e GND (usa o resistor interno INPUT_PULLUP);
           LED: GPIO 2 -> resistor 220 ohm -> LED -> GND.
  Com INPUT_PULLUP: solto = HIGH, apertado = LOW.
  Confira o LED da sua placa; use LED externo com resistor de 220 ohm.
*/

const int PINO_LED = 2;
const int PINO_BOTAO = 15;

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
}

void loop() {
  int lido = digitalRead(PINO_BOTAO);
  if (lido == LOW) {  // apertado
    digitalWrite(PINO_LED, HIGH);
    Serial.println("Botao apertado");
  } else {
    digitalWrite(PINO_LED, LOW);
  }
  delay(50);
}

/*
  EXERCICIOS
  1) Inverta: LED aceso enquanto o botao esta SOLTO.
  2) Faca o botao alternar (liga/desliga) o LED a cada clique.
  3) Conte quantas vezes o botao foi apertado e mostre na serial.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
