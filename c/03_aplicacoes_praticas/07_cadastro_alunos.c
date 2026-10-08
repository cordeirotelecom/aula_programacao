/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

struct Aluno {
    char nome[20];
    int matricula;
    float nota;
};

/* APLICACAO - Cadastro de alunos (vetor de structs)
   Os dados ja estao no codigo para simplificar. */
int main(void)
{
    struct Aluno turma[3] = {
        {"Ana",   101, 8.5f},
        {"Bruno", 102, 5.0f},
        {"Carla", 103, 9.2f}
    };

    printf("MATRICULA  NOME      NOTA\n");
    for (int i = 0; i < 3; i++) {
        printf("%-10d %-9s %.1f\n", turma[i].matricula, turma[i].nome, turma[i].nota);
    }

    return 0;
}

/* EXERCICIOS:
   1. Adicione um quarto aluno.
   2. Mostre o nome do aluno com a maior nota.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 07_cadastro_alunos */
