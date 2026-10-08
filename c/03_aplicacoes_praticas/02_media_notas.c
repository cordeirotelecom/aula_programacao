/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* APLICACAO - Media de notas
   Le 4 notas, calcula a media e informa se foi aprovado (media >= 6). */
int main(void)
{
    float notas[4];
    float soma = 0;

    for (int i = 0; i < 4; i++) {
        printf("Digite a nota %d: ", i + 1);
        if (scanf("%f", &notas[i]) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }
        soma += notas[i];
    }

    float media = soma / 4;
    printf("Media: %.2f\n", media);
    printf(media >= 6.0f ? "Situacao: APROVADO\n" : "Situacao: REPROVADO\n");

    return 0;
}

/* EXERCICIOS:
   1. Mostre tambem a maior e a menor nota.
   2. Se a media estiver entre 4 e 6, mostre "RECUPERACAO".
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 02_media_notas */
