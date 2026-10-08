// Elaborado pelo Prof. Vagner Cordeiro
#include <iomanip>
#include <iostream>

// AULA 4 - ADC (conversor analogico-digital)
// O ADC transforma uma tensao em um numero.
// Neste exemplo: 0 a 1023 representa 0 V a 5 V.
int main()
{
    int leitura_adc = 512;

    // Regra de tres: tensao = leitura * 5 / 1023
    float tensao = leitura_adc * 5.0f / 1023.0f;

    std::cout << "Leitura do ADC: " << leitura_adc << std::endl;
    std::cout << std::fixed << std::setprecision(2);   // 2 casas decimais
    std::cout << "Tensao medida: " << tensao << " V" << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Teste as leituras 0, 256 e 1023.
//  2. Troque a tensao maxima para 3.3 V e compare os resultados.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 04_leitura_adc
