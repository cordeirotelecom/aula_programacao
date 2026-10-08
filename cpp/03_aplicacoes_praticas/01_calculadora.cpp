// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// APLICACAO - Calculadora simples
// Digite no formato: numero operador numero   (exemplo: 8 * 3)
int main()
{
    double a, b;
    char operador;

    std::cout << "Digite uma conta (ex: 8 * 3): ";
    if (!(std::cin >> a >> operador >> b)) {
        std::cout << "Entrada invalida.\n";
        return 1;
    }

    switch (operador) {
        case '+': std::cout << "Resultado: " << a + b << "\n"; break;
        case '-': std::cout << "Resultado: " << a - b << "\n"; break;
        case '*': std::cout << "Resultado: " << a * b << "\n"; break;
        case '/':
            if (b == 0) std::cout << "Erro: divisao por zero.\n";
            else        std::cout << "Resultado: " << a / b << "\n";
            break;
        default: std::cout << "Operador desconhecido.\n";
    }

    return 0;
}

// EXERCICIOS:
// 1. Repita a calculadora ate o usuario digitar 0 0 0.
// 2. Adicione o operador ^ para potencia (use std::pow de <cmath>).

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 01_calculadora
