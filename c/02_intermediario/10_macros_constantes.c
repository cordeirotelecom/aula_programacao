/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA - Constantes e macros
   #define cria um nome que o pre-processador troca pelo valor.
   const cria uma variavel que nao pode ser alterada.
   Em embarcados, #define e usado para nomear pinos e limites. */
#define PINO_LED 13
#define TEMPERATURA_MAXIMA 30
#define DOBRO(x) ((x) * 2)           /* macro com parametro */

int main(void)
{
    const float PI = 3.14159f;
    int vetor[10];

    printf("LED no pino %d\n", PINO_LED);
    printf("Limite de temperatura: %d graus\n", TEMPERATURA_MAXIMA);
    printf("DOBRO(7) = %d\n", DOBRO(7));
    printf("Area de um circulo de raio 2: %.2f\n", PI * 2 * 2);
    printf("O vetor tem %zu posicoes\n", sizeof(vetor) / sizeof(vetor[0]));

    return 0;
}

/* EXERCICIOS:
   1. Crie a constante PINO_BOTAO com o valor 2 e mostre-a.
   2. Crie a macro QUADRADO(x) e teste com QUADRADO(5).
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 10_macros_constantes */
