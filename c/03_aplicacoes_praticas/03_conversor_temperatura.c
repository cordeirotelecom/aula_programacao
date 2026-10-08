/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* APLICACAO - Conversor de temperatura
   F = C * 9 / 5 + 32      K = C + 273.15 */
int main(void)
{
    float celsius;

    printf("Digite a temperatura em Celsius: ");
    if (scanf("%f", &celsius) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    printf("%.1f C = %.1f F\n", celsius, celsius * 9 / 5 + 32);
    printf("%.1f C = %.2f K\n", celsius, celsius + 273.15f);

    return 0;
}

/* EXERCICIOS:
   1. Faca o caminho inverso: Fahrenheit para Celsius.
   2. Mostre uma tabela de 0 a 100 C, de 10 em 10.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 03_conversor_temperatura */
