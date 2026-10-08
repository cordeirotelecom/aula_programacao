// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>
#include <string>

// AULA - Strings em C++
// std::string e muito mais facil que vetor de char: cresce sozinha,
// junta com + e compara com ==.
int main()
{
    std::string nome = "Ana";
    std::string sobrenome = "Silva";

    std::cout << "Tamanho de \"" << nome << "\": " << nome.size() << " letras\n";

    nome = nome + " " + sobrenome;
    std::cout << "Nome completo: " << nome << "\n";

    if (sobrenome == "Silva") {
        std::cout << "O sobrenome e Silva\n";
    }

    std::cout << "Primeira letra: " << nome[0] << "\n";
    return 0;
}

// EXERCICIOS:
// 1. Troque o nome e o sobrenome pelos seus.
// 2. Use nome.substr(0, 3) para mostrar as 3 primeiras letras.
// 3. Use nome.find("Silva") para descobrir a posicao do sobrenome.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 02_strings
