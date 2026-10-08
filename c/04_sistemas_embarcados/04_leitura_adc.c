/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 4 - ADC (conversor analogico-digital)
   O ADC transforma uma tensao em um numero.
   Neste exemplo: 0 a 1023 representa 0 V a 5 V. */
int main(void)
{
    int leitura_adc = 512;

    /* Regra de tres: tensao = leitura * 5 / 1023 */
    float tensao = leitura_adc * 5.0f / 1023.0f;

    printf("Leitura do ADC: %d\n", leitura_adc);
    printf("Tensao medida: %.2f V\n", tensao);

    return 0;
}

/* EXERCICIOS:
   1. Teste as leituras 0, 256 e 1023.
   2. Troque a tensao maxima para 3.3 V e compare os resultados.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 04_leitura_adc */
