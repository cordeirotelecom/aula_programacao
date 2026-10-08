/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* Fatorial: 5! = 5 * 4 * 3 * 2 * 1.
   A funcao chama a si mesma ate chegar ao caso base (n <= 1). */
long fatorial(int n)
{
    if (n <= 1) {
        return 1;                    /* caso base: para a recursao */
    }
    return n * fatorial(n - 1);      /* chamada recursiva */
}

/* AULA - Recursao
   Cuidado: em microcontroladores a recursao consome memoria de pilha. */
int main(void)
{
    for (int n = 1; n <= 6; n++) {
        printf("%d! = %ld\n", n, fatorial(n));
    }

    return 0;
}

/* EXERCICIOS:
   1. Escreva uma funcao recursiva soma_ate(n) que soma de 1 ate n.
   2. Escreva uma funcao recursiva potencia(base, expoente).
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 07_recursao */
