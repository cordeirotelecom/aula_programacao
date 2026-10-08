// Elaborado pelo Prof. Vagner Cordeiro
#include <algorithm>
#include <iostream>
#include <vector>

// APLICACAO - Ordenacao
// Primeiro a ordenacao por bolha (manual); depois std::sort (biblioteca).
int main()
{
    std::vector<int> v = {42, 7, 19, 3, 25, 11};
    std::vector<int> w = v;

    for (std::size_t i = 0; i + 1 < v.size(); i++) {
        for (std::size_t j = 0; j + 1 < v.size() - i; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }

    std::sort(w.begin(), w.end());

    std::cout << "Bolha:     ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\nstd::sort: ";
    for (int x : w) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

// EXERCICIOS:
// 1. Ordene do maior para o menor (use std::greater<int>() no sort).
// 2. Ordene um vector<std::string> com nomes.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 09_ordenacao
