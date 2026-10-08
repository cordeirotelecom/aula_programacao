// Elaborado pelo Prof. Vagner Cordeiro
/* EXEMPLO 09 - Buzzer tocando uma melodia
   Circuito: buzzer passivo entre o pino 8 e o GND.
   Conceitos: tone(pino, frequencia, duracao), vetores. */

const int PINO_BUZZER = 8;

// Frequencias em Hz: Do, Re, Mi, Fa, Sol
int notas[] = {262, 294, 330, 349, 392};
int duracoes[] = {300, 300, 300, 300, 600};

void setup() {
}

void loop() {
  for (int i = 0; i < 5; i++) {
    tone(PINO_BUZZER, notas[i], duracoes[i]);
    delay(duracoes[i] + 50);        // pausa curta entre as notas
  }
  noTone(PINO_BUZZER);
  delay(2000);
}

/* EXERCICIOS: 1) Toque a escala descendo. 2) Crie o som de uma sirene
   variando a frequencia de 500 a 1000 Hz.
   COMO EXECUTAR: abra no Arduino IDE e clique em Carregar,
   ou simule em https://wokwi.com (adicione um buzzer). */
