// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// EXERCICIO 1 - LED em codigo SOS
// Objetivo: repetir um padrao de piscadas.
// O codigo SOS e: 3 piscadas curtas, 3 longas e 3 curtas.
//
// TODO: complete os trechos para mostrar as piscadas longas e curtas.
// Saida esperada:
// Curta, Curta, Curta, Longa, Longa, Longa, Curta, Curta, Curta
int main()
{
    std::cout << "Sinal SOS:" << std::endl;

    for (int i = 0; i < 3; i++) {
        std::cout << "Curta" << std::endl;
    }

    // TODO: mostre 3 piscadas "Longa" aqui.

    // TODO: mostre mais 3 piscadas "Curta" aqui.

    return 0;
}

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp ex_01_led_sos
