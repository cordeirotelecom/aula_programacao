/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 6 - Repeticoes com for
   for(inicio; condicao; passo) repete os comandos entre chaves. */
int main(void)
{
    for (int contador = 1; contador <= 5; contador++) {
        printf("Contagem: %d\n", contador);
    }

    return 0;
}

/* EXERCICIOS:
   1. Conte de 1 ate 10.
   2. Mostre apenas os numeros pares de 2 ate 20 (use contador += 2).
   3. Mostre a contagem regressiva de 5 ate 1.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 06_repeticoes */
