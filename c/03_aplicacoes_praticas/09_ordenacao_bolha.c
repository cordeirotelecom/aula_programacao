/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* APLICACAO - Ordenacao por bolha (bubble sort)
   Compara vizinhos e troca de lugar quando estao fora de ordem. */
int main(void)
{
    int v[6] = {42, 7, 19, 3, 25, 11};
    int n = 6;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    printf("Ordenado: ");
    for (int i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");

    return 0;
}

/* EXERCICIOS:
   1. Ordene do maior para o menor (troque > por <).
   2. Mostre o vetor a cada passada do laco externo.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 09_ordenacao_bolha */
