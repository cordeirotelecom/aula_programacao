/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  12 - Memoria Preferences
  Objetivo: guardar um contador que NAO se perde ao desligar a placa.
  Ligacao: nenhuma. Aperte o botao RESET ou desligue/ligue: o numero continua.
  A biblioteca Preferences grava na memoria flash (NVS) usando "chave = valor".
*/
#include <Preferences.h>

Preferences prefs;

void setup() {
  Serial.begin(115200);
  delay(1000);

  prefs.begin("curso", false);  // espaco "curso", false = leitura e escrita
  int vezes = prefs.getInt("vezes", 0);  // 0 e o valor padrao se nao existir
  vezes++;
  prefs.putInt("vezes", vezes);
  prefs.end();

  Serial.print("Esta placa ja foi ligada ");
  Serial.print(vezes);
  Serial.println(" vezes.");
}

void loop() {
  // nada a fazer
}

/*
  EXERCICIOS
  1) Guarde tambem um texto (putString / getString), como seu nome.
  2) Apague o contador com prefs.clear() quando o botao BOOT for apertado.
  3) Pesquise: por que nao gravar na flash a cada milissegundo?
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
