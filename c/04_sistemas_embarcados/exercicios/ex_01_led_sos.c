/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* EXERCICIO 1 - LED em codigo SOS
   Objetivo: repetir um padrao de piscadas.
   O codigo SOS e: 3 piscadas curtas, 3 longas e 3 curtas.

   TODO: complete os dois for para mostrar as piscadas longas e curtas.
   Saida esperada:
   Curta, Curta, Curta, Longa, Longa, Longa, Curta, Curta, Curta */
int main(void)
{
    printf("Sinal SOS:\n");

    for (int i = 0; i < 3; i++) {
        printf("Curta\n");
    }

    /* TODO: mostre 3 piscadas "Longa" aqui. */

    /* TODO: mostre mais 3 piscadas "Curta" aqui. */

    return 0;
}

/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c ex_01_led_sos */
