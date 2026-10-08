// Elaborado pelo Prof. Vagner Cordeiro
#include <cctype>
#include <iostream>
#include <string>

// APLICACAO - Contar vogais de uma frase
int main()
{
    std::string frase;
    int vogais = 0;

    std::cout << "Digite uma frase: ";
    if (!std::getline(std::cin, frase)) {
        std::cout << "Entrada invalida.\n";
        return 1;
    }

    for (char letra : frase) {
        char c = static_cast<char>(std::tolower(static_cast<unsigned char>(letra)));
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vogais++;
        }
    }

    std::cout << "A frase tem " << vogais << " vogais.\n";
    return 0;
}

// EXERCICIOS:
// 1. Conte tambem as consoantes (use std::isalpha).
// 2. Mostre a frase em letras maiusculas com std::toupper.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 10_contar_vogais
