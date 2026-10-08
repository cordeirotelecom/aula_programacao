// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 4 - Entrada de dados
// std::cin le o que o usuario digita no teclado.
int main()
{
    int numero;

    std::cout << "Digite um numero inteiro: ";

    // >> guarda o valor digitado na variavel. Falha se nao for numero.
    if (!(std::cin >> numero)) {
        std::cout << "Entrada invalida." << std::endl;
        return 1;
    }

    std::cout << "Voce digitou: " << numero << std::endl;
    std::cout << "O dobro e: " << numero * 2 << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Mostre tambem o triplo do numero.
//  2. Peca dois numeros e mostre a soma deles.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 04_entrada_dados
