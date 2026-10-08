// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 5 - PWM (modulacao por largura de pulso)
// O pino liga e desliga muito rapido. O "duty cycle" e a porcentagem do
// tempo em que ele fica ligado; quanto maior, mais brilho tem o LED.
int main()
{
    int duty_cycle = 50;                 // 0 a 100
    int tempo_ligado = duty_cycle;
    int tempo_desligado = 100 - duty_cycle;

    std::cout << "Brilho do LED: " << duty_cycle << "%" << std::endl;
    std::cout << "Em cada periodo: ligado " << tempo_ligado
              << "%, desligado " << tempo_desligado << "%" << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Teste duty_cycle = 0, 25, 75 e 100.
//  2. Use um for para mostrar de 0 a 100 de 25 em 25.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 05_pwm_led
