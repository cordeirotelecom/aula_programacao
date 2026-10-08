/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  09 - Interrupcao no botao
  Objetivo: reagir ao botao na hora, sem ficar perguntando no loop().
  Ligacao: botao entre GPIO 15 e GND; LED: GPIO 2 -> resistor 220 ohm -> LED -> GND.
  Ideia: a funcao da interrupcao so levanta uma bandeira (flag volatile);
  o loop() faz o trabalho. O debounce ignora os "repiques" do botao.
*/

const int PINO_BOTAO = 15;
const int PINO_LED = 2;

volatile bool botaoApertado = false;  // volatile: muda dentro da interrupcao
volatile unsigned long ultimoTempo = 0;
bool ledLigado = false;

// IRAM_ATTR coloca a funcao na RAM rapida (obrigatorio no ESP32)
void IRAM_ATTR aoApertar() {
  unsigned long agora = millis();
  if (agora - ultimoTempo > 200) {  // debounce de 200 ms
    botaoApertado = true;
    ultimoTempo = agora;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PINO_BOTAO), aoApertar, FALLING);
}

void loop() {
  if (botaoApertado) {
    botaoApertado = false;
    ledLigado = !ledLigado;
    digitalWrite(PINO_LED, ledLigado ? HIGH : LOW);
    Serial.println("Interrupcao! LED alternado");
  }
}

/*
  EXERCICIOS
  1) Diminua o debounce para 20 ms e veja se aparecem cliques duplos.
  2) Conte os cliques em uma variavel volatile e mostre na serial.
  3) Use CHANGE no lugar de FALLING e observe apertar e soltar.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
