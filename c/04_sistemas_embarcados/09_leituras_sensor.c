/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 9 - Varias leituras de sensor
   Guardamos as medidas em um vetor para calcular a media. */
int main(void)
{
    int leituras[4] = {20, 22, 21, 23};
    int soma = 0;

    for (int i = 0; i < 4; i++) {
        printf("Leitura %d: %d\n", i + 1, leituras[i]);
        soma = soma + leituras[i];
    }

    printf("Media das leituras: %d\n", soma / 4);

    return 0;
}

/* EXERCICIOS:
   1. Troque os valores do vetor e confira a media.
   2. Encontre e mostre a maior leitura.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 09_leituras_sensor */
