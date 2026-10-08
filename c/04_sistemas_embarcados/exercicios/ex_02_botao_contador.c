/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* EXERCICIO 2 - Contador de cliques do botao
   Objetivo: contar quantas vezes o botao foi pressionado.
   As leituras abaixo simulam o botao: 1 = pressionado, 0 = solto.

   TODO: some 1 em cliques sempre que a leitura for 1.
   Saida esperada: Total de cliques: 3 */
int main(void)
{
    int leituras[6] = {0, 1, 0, 1, 1, 0};
    int cliques = 0;

    for (int i = 0; i < 6; i++) {
        /* TODO: use um if para contar as leituras iguais a 1. */
        (void)leituras[i];
    }

    printf("Total de cliques: %d\n", cliques);

    return 0;
}

/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c ex_02_botao_contador */
