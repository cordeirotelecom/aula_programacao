/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA 8 - Estados com switch
   Muitos sistemas embarcados funcionam por estados.
   Cada numero abaixo representa um estado do semaforo. */
int main(void)
{
    int estado = 2; /* 0 = vermelho, 1 = amarelo, 2 = verde */

    switch (estado) {
    case 0:
        printf("Semaforo vermelho\n");
        break;
    case 1:
        printf("Semaforo amarelo\n");
        break;
    case 2:
        printf("Semaforo verde\n");
        break;
    default:
        printf("Estado desconhecido\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Teste os estados 0, 1, 2 e 5.
   2. Use um for para mostrar a sequencia 0, 1, 2 repetida duas vezes.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 08_maquina_estados */
