/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 10 - Operacoes com bits
   Registradores de hardware guardam varios pinos em um unico numero.
   Cada bit controla um pino: bit ligado = 1, bit desligado = 0. */
int main(void)
{
    unsigned char registrador = 0;
    unsigned char mascara = 1u << 2; /* Mascara do bit 2: 00000100 */

    registrador = registrador | mascara;  /* OR liga o bit. */
    printf("Registrador com bit 2 ligado: %u\n", registrador);

    if ((registrador & mascara) != 0) {   /* AND testa o bit. */
        printf("O bit 2 esta ligado\n");
    }

    registrador = registrador & (unsigned char)~mascara; /* AND com ~ desliga. */
    printf("Registrador com bit 2 desligado: %u\n", registrador);

    return 0;
}

/* EXERCICIOS:
   1. Ligue tambem o bit 0 e mostre o valor do registrador.
   2. Teste e desligue o bit 5.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 10_operacoes_bits */
