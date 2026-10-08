/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_02 - UART 8N1 bit a bit.
   Quadro: START(0) + 8 bits de dados (LSB primeiro) + STOP(1). Linha ociosa = 1. */
#include <stdio.h>

#define BAUD 9600L

/* Gera os 10 bits do quadro para o byte b */
static void montar_quadro(unsigned char b, int quadro[10])
{
    int i;
    quadro[0] = 0;                       /* start */
    for (i = 0; i < 8; i++)
        quadro[1 + i] = (b >> i) & 1;    /* LSB primeiro */
    quadro[9] = 1;                       /* stop */
}

/* Receptor: decodifica o quadro de volta para um byte */
static int decodificar(const int quadro[10], unsigned char *saida)
{
    int i;
    unsigned char b = 0;
    if (quadro[0] != 0 || quadro[9] != 1) return 0;   /* erro de enquadramento */
    for (i = 0; i < 8; i++)
        b = (unsigned char)(b | (quadro[1 + i] << i));
    *saida = b;
    return 1;
}

static void mostrar(unsigned char b)
{
    int quadro[10], i;
    unsigned char rx = 0;
    montar_quadro(b, quadro);
    printf("Enviando '%c' (0x%02X = %3d)\n", b, b, b);
    printf("  bit : START D0 D1 D2 D3 D4 D5 D6 D7 STOP\n");
    printf("  val :   %d    ", quadro[0]);
    for (i = 1; i <= 8; i++) printf(" %d ", quadro[i]);
    printf("  %d\n", quadro[9]);
    /* forma de onda ASCII */
    printf("  onda: ");
    for (i = 0; i < 10; i++) printf("%s", quadro[i] ? "-" : "_");
    printf("\n");
    if (decodificar(quadro, &rx))
        printf("  recebido: '%c' (0x%02X)  -> OK\n\n", rx, rx);
    else
        printf("  erro de quadro!\n\n");
}

int main(void)
{
    double tbit_us = 1000000.0 / (double)BAUD;
    printf("=== UART 8N1 a %ld baud ===\n", BAUD);
    printf("Tempo por bit : %.2f us\n", tbit_us);
    printf("Bits por quadro: 10 -> %.2f us por byte\n", tbit_us * 10.0);
    printf("Bytes por segundo: %.0f\n\n", (double)BAUD / 10.0);
    mostrar('O');
    mostrar('K');
    return 0;
}

/* EXERCICIOS:
   1) Mude BAUD para 115200 e veja o tempo por bit.
   2) Adicione bit de paridade par (8E1).
   3) Corrompa o bit de stop e veja o "erro de quadro". */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_02_uart_bits */
