/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 6 - UART (comunicacao serial)
   A UART envia dados do microcontrolador para o computador.
   Aqui printf representa o envio da mensagem pela serial. */
int main(void)
{
    int temperatura = 24;

    printf("UART: Temperatura = %d graus\n", temperatura);

    return 0;
}

/* EXERCICIOS:
   1. Envie tambem a umidade (crie a variavel umidade).
   2. Envie os valores no formato: temperatura=24;umidade=60
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 06_comunicacao_uart */
