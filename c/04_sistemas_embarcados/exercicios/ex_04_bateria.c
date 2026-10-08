/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* EXERCICIO 4 - Nivel da bateria com ADC
   Objetivo: converter a leitura do ADC em porcentagem de bateria.
   O ADC vai de 0 (bateria vazia) a 1023 (bateria cheia).
   Formula: porcentagem = leitura * 100 / 1023

   TODO: calcule a porcentagem e mostre "Bateria fraca!" se for menor que 20. */
int main(void)
{
    int leitura_adc = 150;
    int porcentagem = 0; /* TODO: calcule o valor correto. */

    printf("Bateria: %d%%\n", porcentagem);

    /* TODO: mostre o aviso quando a bateria estiver fraca. */

    /* Pare e pense: leitura_adc * 100 / 1023 funciona bem com int? */
    (void)leitura_adc;

    return 0;
}

/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c ex_04_bateria */
