// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 6 - UART (comunicacao serial)
// A UART envia dados do microcontrolador para o computador.
// Aqui std::cout representa o envio da mensagem pela serial.
int main()
{
    int temperatura = 24;

    std::cout << "UART: Temperatura = " << temperatura << " graus" << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Envie tambem a umidade (crie a variavel umidade).
//  2. Envie os valores no formato: temperatura=24;umidade=60
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 06_comunicacao_uart
