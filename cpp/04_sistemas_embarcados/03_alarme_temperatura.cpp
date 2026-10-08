// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 3 - Alarme de temperatura
// Sensores medem o ambiente e o programa reage a uma leitura.
int main()
{
    int temperatura = 28; // Leitura simulada do sensor.

    std::cout << "Temperatura: " << temperatura << " graus" << std::endl;

    if (temperatura > 30) {
        std::cout << "Aviso: esta muito quente!" << std::endl;
    } else {
        std::cout << "Temperatura normal" << std::endl;
    }

    return 0;
}

// EXERCICIOS:
//  1. Mude a temperatura para 35 e confira o aviso.
//  2. Adicione um aviso de "muito frio" para temperaturas abaixo de 10.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 03_alarme_temperatura
