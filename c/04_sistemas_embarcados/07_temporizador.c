/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 7 - Temporizador
   Microcontroladores usam temporizadores para medir o tempo.
   Aqui o for simula a passagem de segundos. */
int main(void)
{
    for (int segundo = 1; segundo <= 5; segundo++) {
        printf("Temporizador: %d segundo(s)\n", segundo);

        /* % da o resto da divisao: executa a cada 2 segundos. */
        if (segundo % 2 == 0) {
            printf("  Acao periodica executada\n");
        }
    }

    return 0;
}

/* EXERCICIOS:
   1. Mude a acao periodica para cada 3 segundos.
   2. Aumente o tempo total para 10 segundos.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 07_temporizador */
