/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  06 - Toque capacitivo
  Objetivo: detectar o toque de um dedo em um fio ligado ao GPIO 4.
  Ligacao: um fio solto no GPIO 4 (classico: T0; S3: T4). Toque na ponta do fio.
  Quanto mais perto o dedo, MENOR o valor lido no classico; no S3 o valor SOBE.
  Veja os valores no Monitor Serial e ajuste o limite.
*/

const int PINO_TOQUE = 4;
const int PINO_LED = 2;

#if CONFIG_IDF_TARGET_ESP32S3
const int LIMITE = 40000;  // S3: toque = valor MAIOR que o limite (ajuste!)
#else
const int LIMITE = 30;     // classico: toque = valor MENOR que o limite
#endif

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
}

void loop() {
  int valor = touchRead(PINO_TOQUE);
  Serial.println(valor);
#if CONFIG_IDF_TARGET_ESP32S3
  bool tocou = valor > LIMITE;
#else
  bool tocou = valor < LIMITE;
#endif
  digitalWrite(PINO_LED, tocou ? HIGH : LOW);
  delay(200);
}

/*
  EXERCICIOS
  1) Descubra o limite ideal anotando o valor com e sem toque.
  2) Faca o toque alternar o LED (liga/desliga).
  3) Use dois fios em dois pinos de toque para fazer um "teclado".
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
