/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdlib.h>

/* AULA - Alocacao dinamica de memoria
   malloc reserva memoria durante a execucao; free devolve essa memoria.
   Todo malloc precisa de um free correspondente. */
int main(void)
{
    int quantidade = 5;
    int *leituras = malloc(quantidade * sizeof(int));

    if (leituras == NULL) {          /* sempre confira se deu certo */
        printf("Sem memoria disponivel.\n");
        return 1;
    }

    for (int i = 0; i < quantidade; i++) {
        leituras[i] = (i + 1) * 10;
        printf("leituras[%d] = %d\n", i, leituras[i]);
    }

    free(leituras);                  /* libera a memoria */
    return 0;
}

/* EXERCICIOS:
   1. Mude quantidade para 8.
   2. Calcule e mostre a soma dos valores do vetor dinamico.
   Obs.: em microcontroladores pequenos (como Arduino) evita-se malloc.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 08_alocacao_dinamica */
