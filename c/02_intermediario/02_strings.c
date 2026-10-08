/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <string.h>

/* AULA - Strings (textos)
   Em C, um texto e um vetor de char terminado por '\0'. */
int main(void)
{
    char nome[30] = "Ana";
    char sobrenome[] = "Silva";

    printf("Tamanho de \"%s\": %zu letras\n", nome, strlen(nome));

    strcat(nome, " ");               /* junta textos no final */
    strcat(nome, sobrenome);
    printf("Nome completo: %s\n", nome);

    if (strcmp(sobrenome, "Silva") == 0) {   /* 0 significa: textos iguais */
        printf("O sobrenome e Silva\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Troque o nome e o sobrenome pelos seus.
   2. Mostre o primeiro caractere do nome usando nome[0].
   3. Use strcpy(destino, origem) para copiar um texto para outra variavel.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 02_strings */
