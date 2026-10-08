// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 10 - Operacoes com bits
// Registradores de hardware guardam varios pinos em um unico numero.
// Cada bit controla um pino: bit ligado = 1, bit desligado = 0.
int main()
{
    unsigned int registrador = 0;
    unsigned int mascara = 1u << 2; // Mascara do bit 2: 00000100

    registrador = registrador | mascara; // OR liga o bit.
    std::cout << "Registrador com bit 2 ligado: " << registrador << std::endl;

    if ((registrador & mascara) != 0) {  // AND testa o bit.
        std::cout << "O bit 2 esta ligado" << std::endl;
    }

    registrador = registrador & ~mascara; // AND com ~ desliga o bit.
    std::cout << "Registrador com bit 2 desligado: " << registrador << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Ligue tambem o bit 0 e mostre o valor do registrador.
//  2. Teste e desligue o bit 5.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 10_operacoes_bits
