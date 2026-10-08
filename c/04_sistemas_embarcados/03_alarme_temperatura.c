/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 3 - Alarme de temperatura
   Sensores medem o ambiente e o programa reage a uma leitura. */
int main(void)
{
    int temperatura = 28; /* Leitura simulada do sensor. */

    printf("Temperatura: %d graus\n", temperatura);

    if (temperatura > 30) {
        printf("Aviso: esta muito quente!\n");
    } else {
        printf("Temperatura normal\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Mude a temperatura para 35 e confira o aviso.
   2. Adicione um aviso de "muito frio" para temperaturas abaixo de 10.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 03_alarme_temperatura */
