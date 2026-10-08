// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 2 - Variaveis
// Uma variavel e um nome para um valor guardado na memoria.
int main()
{
    int idade = 18;            // int: numero inteiro
    float temperatura = 23.5f; // float: numero com virgula
    char inicial = 'A';        // char: um unico caractere

    std::cout << "Idade: " << idade << std::endl;
    std::cout << "Temperatura: " << temperatura << " graus" << std::endl;
    std::cout << "Inicial: " << inicial << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Mude a idade e a temperatura e execute novamente.
//  2. Crie uma variavel int chamada ano e mostre o seu valor.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 02_variaveis
