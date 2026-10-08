// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA - while e do-while
// while testa a condicao ANTES de executar; do-while executa pelo menos
// uma vez e testa DEPOIS.
int main()
{
    int energia = 3;

    while (energia > 0) {
        std::cout << "Bateria com " << energia << " barra(s)\n";
        energia--;
    }

    int tentativa = 10;
    do {
        std::cout << "do-while executa ao menos 1 vez (tentativa = " << tentativa << ")\n";
    } while (tentativa < 5);

    return 0;
}

// EXERCICIOS:
// 1. Faca uma contagem regressiva de 10 ate 1 com while.
// 2. Some os numeros de 1 ate 100 usando while e mostre o total (5050).

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 01_while_dowhile
