// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// APLICACAO - Conversor de temperatura
// F = C * 9 / 5 + 32      K = C + 273.15
int main()
{
    float celsius;

    std::cout << "Digite a temperatura em Celsius: ";
    if (!(std::cin >> celsius)) {
        std::cout << "Entrada invalida.\n";
        return 1;
    }

    std::cout << celsius << " C = " << celsius * 9 / 5 + 32 << " F\n";
    std::cout << celsius << " C = " << celsius + 273.15f << " K\n";

    return 0;
}

// EXERCICIOS:
// 1. Faca o caminho inverso: Fahrenheit para Celsius.
// 2. Mostre uma tabela de 0 a 100 C, de 10 em 10.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 03_conversor_temperatura
