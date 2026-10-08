/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA - enum e typedef
   enum cria nomes para numeros; typedef cria um apelido para um tipo.
   Muito usado para estados de maquinas e codigos de erro. */
typedef enum {
    DESLIGADO,   /* vale 0 */
    LIGADO,      /* vale 1 */
    ERRO         /* vale 2 */
} Estado;

typedef unsigned char Byte;     /* Byte passa a ser apelido de unsigned char */

int main(void)
{
    Estado motor = LIGADO;
    Byte velocidade = 200;

    if (motor == LIGADO) {
        printf("Motor ligado a velocidade %u\n", velocidade);
    }

    motor = ERRO;
    printf("Codigo do estado ERRO: %d\n", motor);

    return 0;
}

/* EXERCICIOS:
   1. Adicione o estado EM_MANUTENCAO ao enum.
   2. Use um switch para mostrar o texto de cada estado.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 06_enum_typedef */
