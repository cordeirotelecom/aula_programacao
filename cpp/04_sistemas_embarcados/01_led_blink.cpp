// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 1 - LED (saida digital)
// Em um microcontrolador, um pino pode ficar em nivel alto (true, LED aceso)
// ou baixo (false, LED apagado). Aqui, std::cout simula o LED no computador.
int main()
{
    bool led = false; // false = desligado, true = ligado

    // Cada volta do for e um "ciclo" de tempo.
    for (int ciclo = 1; ciclo <= 4; ciclo++) {
        if (!led) {
            led = true;
            std::cout << "Ciclo " << ciclo << ": LED ligado" << std::endl;
        } else {
            led = false;
            std::cout << "Ciclo " << ciclo << ": LED desligado" << std::endl;
        }
    }

    return 0;
}

// EXERCICIOS:
//  1. Aumente para 10 ciclos.
//  2. Comece com o LED ligado (led = true) e observe a diferenca.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 01_led_blink
