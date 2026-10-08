// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 12 - millis(): fazer duas coisas ao mesmo tempo
   Com delay() o Arduino fica parado. Com millis() (tempo desde que ligou)
   podemos piscar o LED e ainda ler o botao sem travar.
   Circuito: LED no pino 8 (resistor 220 ohm); botao entre pino 2 e GND;
   LED da placa (pino 13) mostra o botao. */

const int LED_PISCA = 8;
const int LED_BOTAO = 13;
const int PINO_BOTAO = 2;

unsigned long ultimaTroca = 0;      // quando o LED trocou pela ultima vez
const unsigned long INTERVALO = 500;
bool ledLigado = false;

void setup() {
  pinMode(LED_PISCA, OUTPUT);
  pinMode(LED_BOTAO, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
}

void loop() {
  unsigned long agora = millis();
  if (agora - ultimaTroca >= INTERVALO) {
    ultimaTroca = agora;
    ledLigado = !ledLigado;
    digitalWrite(LED_PISCA, ledLigado);
  }

  // roda continuamente, sem esperar o LED
  digitalWrite(LED_BOTAO, digitalRead(PINO_BOTAO) == LOW);
}

/* EXERCICIOS: 1) Adicione um segundo LED piscando em outro ritmo (300 ms).
   2) Imprima no Serial a cada 1 segundo, sem delay().
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com. */
