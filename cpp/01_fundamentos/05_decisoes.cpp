// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 5 - Decisoes com if e else
// O programa escolhe um caminho conforme uma condicao.
int main()
{
    int temperatura = 28;

    // Comparadores: > maior, < menor, == igual, >= maior ou igual.
    if (temperatura > 30) {
        std::cout << "Esta quente." << std::endl;
    } else if (temperatura < 15) {
        std::cout << "Esta frio." << std::endl;
    } else {
        std::cout << "A temperatura esta normal." << std::endl;
    }

    return 0;
}

// EXERCICIOS:
//  1. Mude a temperatura para 35 e depois para 10.
//  2. Crie uma variavel nota e mostre "Aprovado" se for 6 ou mais.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 05_decisoes
