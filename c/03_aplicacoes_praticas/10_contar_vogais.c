/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <ctype.h>

/* APLICACAO - Contar vogais de uma frase */
int main(void)
{
    char frase[100];
    int vogais = 0;

    printf("Digite uma frase: ");
    if (fgets(frase, sizeof(frase), stdin) == NULL) {
        printf("Entrada invalida.\n");
        return 1;
    }

    for (int i = 0; frase[i] != '\0'; i++) {
        char c = (char)tolower((unsigned char)frase[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vogais++;
        }
    }

    printf("A frase tem %d vogais.\n", vogais);
    return 0;
}

/* EXERCICIOS:
   1. Conte tambem as consoantes (use isalpha).
   2. Mostre a frase em letras maiusculas com toupper.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 10_contar_vogais */
