/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 5 - Decisoes com if e else
   O programa escolhe um caminho conforme uma condicao. */
int main(void)
{
    int temperatura = 28;

    /* Comparadores: > maior, < menor, == igual, >= maior ou igual. */
    if (temperatura > 30) {
        printf("Esta quente.\n");
    } else if (temperatura < 15) {
        printf("Esta frio.\n");
    } else {
        printf("A temperatura esta normal.\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Mude a temperatura para 35 e depois para 10.
   2. Crie uma variavel nota e mostre "Aprovado" se for 6 ou mais.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 05_decisoes */
