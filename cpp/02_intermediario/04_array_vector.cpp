// Elaborado pelo Prof. Vagner Cordeiro
#include <array>
#include <iostream>
#include <vector>

// AULA - std::array e std::vector
// array tem tamanho fixo; vector cresce com push_back.
int main()
{
    std::array<int, 3> fixo = {18, 22, 25};

    std::vector<int> temperaturas;
    temperaturas.push_back(17);
    temperaturas.push_back(21);
    temperaturas.push_back(26);
    temperaturas.push_back(19);

    int soma = 0;
    for (int t : temperaturas) {            // for para cada elemento
        std::cout << t << " ";
        soma += t;
    }
    std::cout << "-> media: " << soma / static_cast<int>(temperaturas.size()) << "\n";

    std::cout << "Array fixo tem " << fixo.size() << " posicoes, primeira = " << fixo[0] << "\n";

    std::vector<std::vector<int>> matriz = {{1, 2, 3}, {4, 5, 6}};
    std::cout << "matriz[1][2] = " << matriz[1][2] << "\n";

    return 0;
}

// EXERCICIOS:
// 1. Adicione mais duas temperaturas ao vector.
// 2. Mostre a maior temperatura.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 04_array_vector
