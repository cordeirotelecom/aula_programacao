// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// APLICACAO - Sequencia de Fibonacci
// Cada numero e a soma dos dois anteriores: 0 1 1 2 3 5 8 13 ...
int main()
{
    int anterior = 0;
    int atual = 1;

    std::cout << "Os 15 primeiros numeros de Fibonacci:\n";
    for (int i = 0; i < 15; i++) {
        std::cout << anterior << " ";
        int proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    std::cout << "\n";

    return 0;
}

// EXERCICIOS:
// 1. Mostre 20 numeros em vez de 15.
// 2. Pergunte ao usuario quantos numeros mostrar.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 06_fibonacci
