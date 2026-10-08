// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>
#include <random>

// APLICACAO - Jogo de adivinhacao
// O computador sorteia um numero de 1 a 100; voce tem 7 tentativas.
int main()
{
    std::random_device dispositivo;
    std::mt19937 gerador(dispositivo());
    std::uniform_int_distribution<int> sorteio(1, 100);
    int segredo = sorteio(gerador);
    int palpite;

    for (int tentativa = 1; tentativa <= 7; tentativa++) {
        std::cout << "Tentativa " << tentativa << " - seu palpite: ";
        if (!(std::cin >> palpite)) {
            std::cout << "Entrada encerrada.\n";
            return 1;
        }
        if (palpite == segredo) {
            std::cout << "Acertou em " << tentativa << " tentativa(s)!\n";
            return 0;
        }
        std::cout << (palpite < segredo ? "Maior...\n" : "Menor...\n");
    }

    std::cout << "Acabaram as tentativas. O numero era " << segredo << ".\n";
    return 0;
}

// EXERCICIOS:
// 1. Mude o intervalo para 1 a 50.
// 2. Permita jogar de novo ao final.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 08_jogo_adivinhacao
