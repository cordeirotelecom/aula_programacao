/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 2 - Variaveis
   Uma variavel e um nome para um valor guardado na memoria. */
int main(void)
{
    int idade = 18;            /* int: numero inteiro */
    float temperatura = 23.5f; /* float: numero com virgula */
    char inicial = 'A';        /* char: um unico caractere */

    /* %d mostra int, %f mostra float, %c mostra char. */
    printf("Idade: %d\n", idade);
    printf("Temperatura: %.1f graus\n", temperatura);
    printf("Inicial: %c\n", inicial);

    return 0;
}

/* EXERCICIOS:
   1. Mude a idade e a temperatura e execute novamente.
   2. Crie uma variavel int chamada ano e mostre o seu valor.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 02_variaveis */
