/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 1 - LED (saida digital)
   Em um microcontrolador, um pino pode ficar em nivel alto (1, LED aceso)
   ou baixo (0, LED apagado). Aqui, printf simula o LED no computador. */
int main(void)
{
    int led = 0; /* 0 = desligado, 1 = ligado */

    /* Cada volta do for e um "ciclo" de tempo. */
    for (int ciclo = 1; ciclo <= 4; ciclo++) {
        if (led == 0) {
            led = 1;
            printf("Ciclo %d: LED ligado\n", ciclo);
        } else {
            led = 0;
            printf("Ciclo %d: LED desligado\n", ciclo);
        }
    }

    return 0;
}

/* EXERCICIOS:
   1. Aumente para 10 ciclos.
   2. Comece com o LED ligado (led = 1) e observe a diferenca.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 01_led_blink */
