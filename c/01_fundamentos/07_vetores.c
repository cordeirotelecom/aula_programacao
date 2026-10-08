/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 7 - Vetores
   Um vetor (array) guarda varios valores do mesmo tipo.
   As posicoes comecam em 0: leituras[0], leituras[1], leituras[2]. */
int main(void)
{
    int leituras[3] = {20, 22, 21};

    for (int i = 0; i < 3; i++) {
        printf("Leitura %d: %d\n", i + 1, leituras[i]);
    }

    return 0;
}

/* EXERCICIOS:
   1. Aumente o vetor para 5 leituras (lembre de mudar o for).
   2. Calcule e mostre a soma das leituras.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 07_vetores */
