// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// Referencia (&): a funcao recebe a propria variavel, sem copia.
void aumentar(int &valor)
{
    valor = valor + 10;
}

// AULA - Ponteiros e referencias
// Ponteiro guarda um endereco; referencia e um "outro nome" para a variavel.
int main()
{
    int numero = 5;
    int *p = &numero;

    std::cout << "Valor de numero: " << numero << "\n";
    std::cout << "Valor lido pelo ponteiro: " << *p << "\n";

    *p = 20;
    std::cout << "Depois de *p = 20, numero vale: " << numero << "\n";

    aumentar(numero);               // sem precisar de & na chamada
    std::cout << "Depois de aumentar(), numero vale: " << numero << "\n";

    int &apelido = numero;          // apelido e outro nome de numero
    apelido = 1;
    std::cout << "Depois de apelido = 1, numero vale: " << numero << "\n";

    return 0;
}

// EXERCICIOS:
// 1. Crie a funcao dobrar(int &valor) que multiplica o valor por 2.
// 2. Crie a funcao trocar(int &a, int &b) que troca os valores.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 03_ponteiros_referencias
