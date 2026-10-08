// Elaborado pelo Prof. Vagner Cordeiro
#include <cstdint>
#include <iostream>

// AULA - enum class e using
// enum class e mais seguro que enum: os nomes ficam dentro do tipo.
enum class Estado { Desligado, Ligado, Erro };

using Byte = std::uint8_t;          // "using" cria apelido de tipo

int main()
{
    Estado motor = Estado::Ligado;
    Byte velocidade = 200;

    if (motor == Estado::Ligado) {
        std::cout << "Motor ligado a velocidade " << static_cast<int>(velocidade) << "\n";
    }

    motor = Estado::Erro;
    std::cout << "Codigo do estado Erro: " << static_cast<int>(motor) << "\n";

    return 0;
}

// EXERCICIOS:
// 1. Adicione o estado EmManutencao ao enum class.
// 2. Use um switch para mostrar o texto de cada estado.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 06_enum_class
