/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 2 - Botao (entrada digital)
   Um botao e lido como 1 (pressionado) ou 0 (solto).
   O programa le a entrada e decide o que fazer com o LED. */
int main(void)
{
    int botao = 1; /* Mude para 0 e execute de novo. */

    if (botao == 1) {
        printf("Botao pressionado: ligar LED\n");
    } else {
        printf("Botao solto: desligar LED\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Mude botao para 0 e veja o resultado.
   2. Crie uma segunda variavel, botao_b, e ligue o LED somente
      se os dois botoes estiverem pressionados (use &&).
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 02_entrada_digital */
