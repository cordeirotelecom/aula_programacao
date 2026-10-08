// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// Fatorial recursivo: a funcao chama a si mesma ate o caso base (n <= 1).
long fatorial(int n)
{
    if (n <= 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}

// AULA - Recursao
int main()
{
    for (int n = 1; n <= 6; n++) {
        std::cout << n << "! = " << fatorial(n) << "\n";
    }
    return 0;
}

// EXERCICIOS:
// 1. Escreva uma funcao recursiva soma_ate(n) que soma de 1 ate n.
// 2. Escreva uma funcao recursiva potencia(base, expoente).

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 07_recursao
