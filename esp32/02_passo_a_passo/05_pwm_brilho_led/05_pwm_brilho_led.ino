/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  05 - PWM: brilho do LED
  Objetivo: aumentar e diminuir o brilho do LED aos poucos (fade).
  Ligacao: GPIO 2 -> resistor 220 ohm -> LED -> GND (ou LED externo).
  ATENCAO: ledcAttach/ledcWrite com pino exigem o core ESP32 versao 3.0 ou maior.
*/

const int PINO_LED = 2;
const int FREQUENCIA = 5000;  // 5 kHz
const int RESOLUCAO = 8;      // 8 bits: duty de 0 a 255

int brilho = 0;
int passo = 5;

void setup() {
  ledcAttach(PINO_LED, FREQUENCIA, RESOLUCAO);  // liga o PWM ao pino
}

void loop() {
  ledcWrite(PINO_LED, brilho);
  brilho += passo;
  if (brilho <= 0 || brilho >= 255) {
    passo = -passo;  // inverte o sentido nos limites
  }
  delay(20);
}

/*
  EXERCICIOS
  1) Deixe o fade mais lento mudando o delay.
  2) Troque a RESOLUCAO para 10 bits (duty 0 a 1023) e ajuste o codigo.
  3) Controle o brilho com o potenciometro do exemplo 04.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
