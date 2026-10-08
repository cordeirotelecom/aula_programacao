// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 9 - Varias leituras de sensor
// Guardamos as medidas em um vetor para calcular a media.
int main()
{
    int leituras[4] = {20, 22, 21, 23};
    int soma = 0;

    for (int i = 0; i < 4; i++) {
        std::cout << "Leitura " << i + 1 << ": " << leituras[i] << std::endl;
        soma = soma + leituras[i];
    }

    std::cout << "Media das leituras: " << soma / 4 << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Troque os valores do vetor e confira a media.
//  2. Encontre e mostre a maior leitura.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 09_leituras_sensor
