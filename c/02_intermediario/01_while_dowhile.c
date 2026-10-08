/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA - while e do-while
   while testa a condicao ANTES de executar; do-while executa pelo menos
   uma vez e testa DEPOIS. Use while quando nao se sabe quantas repeticoes. */
int main(void)
{
    int energia = 3;

    while (energia > 0) {
        printf("Bateria com %d barra(s)\n", energia);
        energia--;                 /* energia = energia - 1 */
    }

    int tentativa = 10;
    do {
        printf("do-while executa ao menos 1 vez (tentativa = %d)\n", tentativa);
    } while (tentativa < 5);       /* condicao falsa, mas ja executou uma vez */

    return 0;
}

/* EXERCICIOS:
   1. Faca uma contagem regressiva de 10 ate 1 com while.
   2. Some os numeros de 1 ate 100 usando while e mostre o total (5050).
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 01_while_dowhile */
