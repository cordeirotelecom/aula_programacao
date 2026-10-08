/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* Recebe o ENDERECO da variavel, por isso consegue altera-la. */
void aumentar(int *valor)
{
    *valor = *valor + 10;
}

/* AULA - Ponteiros
   Um ponteiro guarda o endereco de memoria de outra variavel.
   & obtem o endereco; * acessa o valor guardado nesse endereco.
   Em sistemas embarcados, ponteiros acessam registradores e memoria. */
int main(void)
{
    int numero = 5;
    int *p = &numero;            /* p aponta para numero */

    printf("Valor de numero: %d\n", numero);
    printf("Valor lido pelo ponteiro: %d\n", *p);

    *p = 20;                     /* altera numero pelo ponteiro */
    printf("Depois de *p = 20, numero vale: %d\n", numero);

    aumentar(&numero);
    printf("Depois de aumentar(), numero vale: %d\n", numero);

    return 0;
}

/* EXERCICIOS:
   1. Crie a funcao dobrar(int *valor) que multiplica o valor por 2.
   2. Crie a funcao trocar(int *a, int *b) que troca os valores das variaveis.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 03_ponteiros */
