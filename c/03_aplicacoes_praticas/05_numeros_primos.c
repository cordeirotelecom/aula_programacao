/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* Retorna 1 se n e primo (so divisivel por 1 e por ele mesmo). */
int eh_primo(int n)
{
    if (n < 2) return 0;
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) return 0;
    }
    return 1;
}

/* APLICACAO - Numeros primos ate um limite */
int main(void)
{
    int limite;

    printf("Mostrar primos ate: ");
    if (scanf("%d", &limite) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    for (int n = 2; n <= limite; n++) {
        if (eh_primo(n)) printf("%d ", n);
    }
    printf("\n");

    return 0;
}

/* EXERCICIOS:
   1. Conte quantos primos foram encontrados e mostre o total.
   2. Verifique se um unico numero digitado e primo.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 05_numeros_primos */
