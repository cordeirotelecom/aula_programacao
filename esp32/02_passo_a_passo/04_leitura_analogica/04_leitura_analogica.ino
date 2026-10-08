/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  04 - Leitura analogica
  Objetivo: ler um potenciometro (valor de 0 a 4095) e mostrar na serial.
  Ligacao: extremos do potenciometro em 3V3 e GND; pino do meio no pino abaixo.
  Classico: GPIO 34 (so entrada, ADC1). S3: GPIO 4 (ADC1).
  Evite ADC2 quando usar WiFi.
*/

#if CONFIG_IDF_TARGET_ESP32S3
const int PINO_POT = 4;
#else
const int PINO_POT = 34;
#endif

void setup() {
  Serial.begin(115200);
}

void loop() {
  int valor = analogRead(PINO_POT);           // 0 a 4095 (12 bits)
  int porcento = map(valor, 0, 4095, 0, 100);  // converte para 0 a 100
  Serial.print("Valor: ");
  Serial.print(valor);
  Serial.print("  Porcentagem: ");
  Serial.println(porcento);
  delay(300);
}

/*
  EXERCICIOS
  1) Mostre a tensao: valor * 3.3 / 4095.0.
  2) Acenda um LED quando passar de 50%.
  3) Use Ferramentas > Plotter Serial e gire o potenciometro.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
