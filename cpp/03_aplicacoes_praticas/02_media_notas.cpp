// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>
#include <vector>

// APLICACAO - Media de notas
// Le 4 notas, calcula a media e informa se foi aprovado (media >= 6).
int main()
{
    std::vector<float> notas;
    float soma = 0;

    for (int i = 0; i < 4; i++) {
        float nota;
        std::cout << "Digite a nota " << i + 1 << ": ";
        if (!(std::cin >> nota)) {
            std::cout << "Entrada invalida.\n";
            return 1;
        }
        notas.push_back(nota);
        soma += nota;
    }

    float media = soma / static_cast<float>(notas.size());
    std::cout << "Media: " << media << "\n";
    std::cout << (media >= 6.0f ? "Situacao: APROVADO\n" : "Situacao: REPROVADO\n");

    return 0;
}

// EXERCICIOS:
// 1. Mostre tambem a maior e a menor nota (std::max_element / std::min_element).
// 2. Se a media estiver entre 4 e 6, mostre "RECUPERACAO".

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 02_media_notas
