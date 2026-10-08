/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA - Matrizes (vetores com linhas e colunas)
   Exemplo: temperaturas medidas em 3 dias, 4 vezes por dia. */
int main(void)
{
    int temperaturas[3][4] = {
        {18, 22, 25, 20},
        {17, 21, 26, 19},
        {16, 23, 27, 21}
    };

    for (int dia = 0; dia < 3; dia++) {
        int soma = 0;
        for (int medida = 0; medida < 4; medida++) {
            printf("%3d ", temperaturas[dia][medida]);
            soma += temperaturas[dia][medida];
        }
        printf("-> media do dia %d: %d\n", dia + 1, soma / 4);
    }

    return 0;
}

/* EXERCICIOS:
   1. Mostre a maior temperatura de toda a matriz.
   2. Adicione um quarto dia na matriz.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 04_matrizes */
