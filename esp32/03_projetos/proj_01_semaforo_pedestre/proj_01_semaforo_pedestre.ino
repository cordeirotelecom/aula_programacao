/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  PROJETO 1 - Semaforo com botao de pedestre (maquina de estados)

  OBJETIVO
    Um semaforo de carros (3 LEDs) que fica VERDE ate alguem apertar o botao do
    pedestre. Entao passa para AMARELO, VERMELHO (pedestre atravessa) e volta ao VERDE.

  MATERIAIS
    ESP32 ou ESP32-S3, protoboard, 3 LEDs (vermelho, amarelo, verde),
    3 resistores de 220 ohm, 1 botao, jumpers.

  LIGACAO (funciona no classico e no S3)
    GPIO 16 -> 220 ohm -> LED vermelho -> GND
    GPIO 17 -> 220 ohm -> LED amarelo  -> GND
    GPIO 18 -> 220 ohm -> LED verde    -> GND
    Botao entre GPIO 15 e GND (INPUT_PULLUP)

  PASSO A PASSO
    1) Monte o circuito. 2) Carregue o codigo. 3) O LED verde acende.
    4) Aperte o botao: depois de 3 s minimos de verde, vai para amarelo (2 s),
       vermelho (5 s) e volta ao verde.

  COMO TESTAR
    Abra o Monitor Serial (115200) para ver o estado atual a cada mudanca.
    A maquina de estados usa millis(), entao nao trava com delay().
*/

const int PINO_VERMELHO = 16;
const int PINO_AMARELO = 17;
const int PINO_VERDE = 18;
const int PINO_BOTAO = 15;

enum Estado { VERDE, AMARELO, VERMELHO };
Estado estado = VERDE;

unsigned long inicioEstado = 0;
bool pedido = false;  // alguem apertou o botao?

void mudarPara(Estado novo) {
  estado = novo;
  inicioEstado = millis();
  digitalWrite(PINO_VERDE, novo == VERDE);
  digitalWrite(PINO_AMARELO, novo == AMARELO);
  digitalWrite(PINO_VERMELHO, novo == VERMELHO);
  if (novo == VERDE) Serial.println("Estado: VERDE (carros passam)");
  if (novo == AMARELO) Serial.println("Estado: AMARELO (atencao)");
  if (novo == VERMELHO) Serial.println("Estado: VERMELHO (pedestre atravessa)");
}

void setup() {
  Serial.begin(115200);
  pinMode(PINO_VERMELHO, OUTPUT);
  pinMode(PINO_AMARELO, OUTPUT);
  pinMode(PINO_VERDE, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  mudarPara(VERDE);
}

void loop() {
  if (digitalRead(PINO_BOTAO) == LOW) pedido = true;  // guarda o pedido

  unsigned long decorrido = millis() - inicioEstado;

  switch (estado) {
    case VERDE:
      if (pedido && decorrido > 3000) mudarPara(AMARELO);
      break;
    case AMARELO:
      if (decorrido > 2000) mudarPara(VERMELHO);
      break;
    case VERMELHO:
      if (decorrido > 5000) {
        pedido = false;
        mudarPara(VERDE);
      }
      break;
  }
}

/*
  EXERCICIOS
  1) Aumente o tempo do vermelho para 8 segundos.
  2) Faca o amarelo piscar durante o estado AMARELO.
  3) Adicione um LED verde de pedestre aceso so no VERMELHO dos carros.
  4) Mostre na serial quantos pedidos de travessia ja foram atendidos.
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
