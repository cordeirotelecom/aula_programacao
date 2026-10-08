// Elaborado pelo Prof. Vagner Cordeiro
#include <iomanip>
#include <iostream>

// APLICACAO - Tabuada
int main()
{
    int numero;

    std::cout << "Tabuada de qual numero? ";
    if (!(std::cin >> numero)) {
        std::cout << "Entrada invalida.\n";
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        std::cout << numero << " x " << std::setw(2) << i << " = "
                  << std::setw(3) << numero * i << "\n";
    }

    return 0;
}

// EXERCICIOS:
// 1. Mostre a tabuada ate 20 em vez de 10.
// 2. Mostre as tabuadas de 1 ate 9 de uma vez (dois for aninhados).

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 04_tabuada
