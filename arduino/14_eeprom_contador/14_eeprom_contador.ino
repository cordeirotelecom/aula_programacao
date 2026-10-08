// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 14 - EEPROM: memoria que nao apaga ao desligar
   Conta quantas vezes a placa foi ligada. Desligue e ligue de novo:
   o numero continua crescendo.
   Conceitos: biblioteca EEPROM (read/write/update).
   Cuidado: a EEPROM tem ~100 mil gravacoes por posicao. */
#include <EEPROM.h>

const int ENDERECO = 0;             // posicao da memoria usada

void setup() {
  Serial.begin(9600);

  byte vezes = EEPROM.read(ENDERECO);
  if (vezes == 255) {               // 255 = memoria nova, nunca gravada
    vezes = 0;
  }
  vezes++;
  EEPROM.update(ENDERECO, vezes);   // grava somente se o valor mudou

  Serial.print("Esta placa foi ligada ");
  Serial.print(vezes);
  Serial.println(" vez(es).");
}

void loop() {
}

/* EXERCICIOS: 1) Zere o contador quando um botao for pressionado no
   inicio. 2) Guarde tambem a maior temperatura ja lida.
   COMO EXECUTAR: abra no Arduino IDE, clique em Carregar, abra o Monitor
   Serial (9600 baud) e aperte o botao RESET da placa varias vezes. */
