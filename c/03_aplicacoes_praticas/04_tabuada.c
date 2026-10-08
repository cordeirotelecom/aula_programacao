/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* APLICACAO - Tabuada */
int main(void)
{
    int numero;

    printf("Tabuada de qual numero? ");
    if (scanf("%d", &numero) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        printf("%d x %2d = %3d\n", numero, i, numero * i);
    }

    return 0;
}

/* EXERCICIOS:
   1. Mostre a tabuada ate 20 em vez de 10.
   2. Mostre as tabuadas de 1 ate 9 de uma vez (dois for aninhados).
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 04_tabuada */
