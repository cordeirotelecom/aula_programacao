/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 3 - Operacoes matematicas
   Operadores: + soma, - subtracao, * multiplicacao, / divisao, % resto. */
int main(void)
{
    int a = 10;
    int b = 3;

    printf("Soma: %d\n", a + b);
    printf("Subtracao: %d\n", a - b);
    printf("Multiplicacao: %d\n", a * b);
    printf("Divisao inteira: %d\n", a / b); /* 10 / 3 = 3, sem a parte decimal. */
    printf("Resto da divisao: %d\n", a % b);

    return 0;
}

/* EXERCICIOS:
   1. Troque a e b por outros valores.
   2. Calcule a media de a e b: (a + b) / 2.
   3. Por que 10 / 3 mostra 3? Pesquise a diferenca entre int e float.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 03_operacoes */
