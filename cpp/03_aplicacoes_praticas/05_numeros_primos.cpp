// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// Retorna true se n e primo (so divisivel por 1 e por ele mesmo).
bool eh_primo(int n)
{
    if (n < 2) return false;
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) return false;
    }
    return true;
}

// APLICACAO - Numeros primos ate um limite
int main()
{
    int limite;

    std::cout << "Mostrar primos ate: ";
    if (!(std::cin >> limite)) {
        std::cout << "Entrada invalida.\n";
        return 1;
    }

    for (int n = 2; n <= limite; n++) {
        if (eh_primo(n)) std::cout << n << " ";
    }
    std::cout << "\n";

    return 0;
}

// EXERCICIOS:
// 1. Conte quantos primos foram encontrados e mostre o total.
// 2. Verifique se um unico numero digitado e primo.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 05_numeros_primos
