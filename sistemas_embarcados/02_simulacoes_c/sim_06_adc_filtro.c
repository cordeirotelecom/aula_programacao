/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_06 - ADC de 10 bits simulado, ruido, media movel, tensao e temperatura.
   Sensor simulado: LM35 (10 mV por grau Celsius), referencia 5.0 V. */
#include <stdio.h>

#define VREF 5.0
#define ADC_MAX 1023
#define JANELA 4

static unsigned long semente = 12345UL;

/* gerador pseudoaleatorio simples (deterministico) */
static int ruido(void)
{
    semente = (semente * 1103515245UL + 12345UL) & 0x7FFFFFFFUL;
    return (int)((semente >> 16) % 9) - 4;   /* de -4 a +4 */
}

int main(void)
{
    int amostras[JANELA] = { 0 };
    int i, soma;
    int real = 102;   /* leitura "verdadeira": 102/1023*5 V = 0.4985 V -> ~49.9 C */

    printf("ADC 10 bits: 0..%d  |  1 LSB = %.2f mV\n\n", ADC_MAX, VREF * 1000.0 / (ADC_MAX + 1));
    printf(" n | bruto | media | tensao(V) | temp(C)\n");
    printf("---+-------+-------+-----------+--------\n");
    for (i = 0; i < 12; i++) {
        int bruto = real + ruido();
        int k;
        double v, temp;
        amostras[i % JANELA] = bruto;
        soma = 0;
        for (k = 0; k < JANELA; k++) soma += amostras[k];
        /* nas primeiras leituras a janela ainda tem zeros: divide so pelo que ja existe */
        {
            int validas = (i + 1 < JANELA) ? i + 1 : JANELA;
            int media = soma / validas;
            v = media * VREF / ADC_MAX;
            temp = v * 100.0;   /* 10 mV/C */
            printf("%2d | %5d | %5d | %9.3f | %6.1f\n", i + 1, bruto, media, v, temp);
        }
    }
    printf("\nA media movel suaviza o ruido, mas deixa a resposta mais lenta.\n");
    return 0;
}

/* EXERCICIOS:
   1) Aumente JANELA para 8 e compare a suavizacao.
   2) Use VREF 3.3 e recalcule a temperatura.
   3) Troque para ADC de 12 bits (4095) e veja a resolucao em mV. */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_06_adc_filtro */
