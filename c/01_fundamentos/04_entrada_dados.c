/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 4 - Entrada de dados
   scanf le o que o usuario digita no teclado. */
int main(void)
{
    int numero;

    printf("Digite um numero inteiro: ");

    /* &numero informa onde guardar o valor lido.
       scanf devolve 1 quando consegue ler um numero. */
    if (scanf("%d", &numero) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    printf("Voce digitou: %d\n", numero);
    printf("O dobro e: %d\n", numero * 2);

    return 0;
}

/* EXERCICIOS:
   1. Mostre tambem o triplo do numero.
   2. Peca dois numeros e mostre a soma deles.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 04_entrada_dados */
