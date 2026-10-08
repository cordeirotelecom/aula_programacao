// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 2 - Botao (entrada digital)
// Um botao e lido como pressionado (true) ou solto (false).
// O programa le a entrada e decide o que fazer com o LED.
int main()
{
    bool botao = true; // Mude para false e execute de novo.

    if (botao) {
        std::cout << "Botao pressionado: ligar LED" << std::endl;
    } else {
        std::cout << "Botao solto: desligar LED" << std::endl;
    }

    return 0;
}

// EXERCICIOS:
//  1. Mude botao para false e veja o resultado.
//  2. Crie uma segunda variavel, botao_b, e ligue o LED somente
//     se os dois botoes estiverem pressionados (use &&).
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 02_entrada_digital
