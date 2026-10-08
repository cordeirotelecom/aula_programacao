/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA - Estruturas (struct)
   Uma struct agrupa dados diferentes que formam uma unica coisa. */
struct Sensor {
    int id;
    float temperatura;
    int ativo;
};

int main(void)
{
    struct Sensor s1 = {1, 23.5f, 1};
    struct Sensor s2 = {2, 31.0f, 0};

    printf("Sensor %d: %.1f graus, %s\n", s1.id, s1.temperatura,
           s1.ativo ? "ativo" : "inativo");
    printf("Sensor %d: %.1f graus, %s\n", s2.id, s2.temperatura,
           s2.ativo ? "ativo" : "inativo");

    s2.ativo = 1;                /* altera um campo com o ponto */
    printf("Sensor 2 foi ativado.\n");

    return 0;
}

/* EXERCICIOS:
   1. Crie uma struct Aluno com nome (char[30]) e nota (float).
   2. Crie um vetor com 3 sensores e mostre todos com um for.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 05_structs */
