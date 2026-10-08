/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* APLICACAO - Jogo de adivinhacao
   O computador sorteia um numero de 1 a 100; voce tem 7 tentativas. */
int main(void)
{
    srand((unsigned)time(NULL));         /* muda a sequencia a cada execucao */
    int segredo = rand() % 100 + 1;
    int palpite;

    for (int tentativa = 1; tentativa <= 7; tentativa++) {
        printf("Tentativa %d - seu palpite: ", tentativa);
        if (scanf("%d", &palpite) != 1) {
            printf("Entrada encerrada.\n");
            return 1;
        }
        if (palpite == segredo) {
            printf("Acertou em %d tentativa(s)!\n", tentativa);
            return 0;
        }
        printf(palpite < segredo ? "Maior...\n" : "Menor...\n");
    }

    printf("Acabaram as tentativas. O numero era %d.\n", segredo);
    return 0;
}

/* EXERCICIOS:
   1. Mude o intervalo para 1 a 50.
   2. Permita jogar de novo ao final.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 08_jogo_adivinhacao */
