/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* APLICACAO - Calculadora simples
   Digite no formato: numero operador numero   (exemplo: 8 * 3) */
int main(void)
{
    double a, b;
    char operador;

    printf("Digite uma conta (ex: 8 * 3): ");
    if (scanf("%lf %c %lf", &a, &operador, &b) != 3) {
        printf("Entrada invalida.\n");
        return 1;
    }

    switch (operador) {
        case '+': printf("Resultado: %.2f\n", a + b); break;
        case '-': printf("Resultado: %.2f\n", a - b); break;
        case '*': printf("Resultado: %.2f\n", a * b); break;
        case '/':
            if (b == 0) printf("Erro: divisao por zero.\n");
            else        printf("Resultado: %.2f\n", a / b);
            break;
        default: printf("Operador desconhecido.\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Adicione o operador % (resto) para numeros inteiros.
   2. Repita a calculadora ate o usuario digitar 0 0 0.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 01_calculadora */
