// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 3 - Operacoes matematicas
// Operadores: + soma, - subtracao, * multiplicacao, / divisao, % resto.
int main()
{
    int a = 10;
    int b = 3;

    std::cout << "Soma: " << a + b << std::endl;
    std::cout << "Subtracao: " << a - b << std::endl;
    std::cout << "Multiplicacao: " << a * b << std::endl;
    std::cout << "Divisao inteira: " << a / b << std::endl; // 10 / 3 = 3
    std::cout << "Resto da divisao: " << a % b << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Troque a e b por outros valores.
//  2. Calcule a media de a e b: (a + b) / 2.
//  3. Por que 10 / 3 mostra 3? Pesquise a diferenca entre int e float.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 03_operacoes
