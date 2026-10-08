// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 13 - Interrupcao por botao
   Uma interrupcao pausa o loop() na hora do evento, sem precisar ficar
   verificando o botao.
   Circuito: botao entre o pino 2 (suporta interrupcao no Uno) e GND;
   LED no pino 8 com resistor 220 ohm. */

const int PINO_BOTAO = 2;
const int PINO_LED = 8;

volatile bool ledLigado = false;    // volatile: muda dentro da interrupcao

void alternarLed() {                // rotina de interrupcao: deve ser curta
  ledLigado = !ledLigado;
}

void setup() {
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BOTAO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PINO_BOTAO), alternarLed, FALLING);
}

void loop() {
  digitalWrite(PINO_LED, ledLigado);
  delay(100);
}

/* EXERCICIOS: 1) Conte quantos cliques ocorreram e mostre no Serial.
   2) Ignore cliques com menos de 200 ms de intervalo (debounce).
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com. */
