/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* APLICACAO - Sequencia de Fibonacci
   Cada numero e a soma dos dois anteriores: 0 1 1 2 3 5 8 13 ... */
int main(void)
{
    int anterior = 0;
    int atual = 1;

    printf("Os 15 primeiros numeros de Fibonacci:\n");
    for (int i = 0; i < 15; i++) {
        printf("%d ", anterior);
        int proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    printf("\n");

    return 0;
}

/* EXERCICIOS:
   1. Mostre 20 numeros em vez de 15.
   2. Pergunte ao usuario quantos numeros mostrar.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 06_fibonacci */
