// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>
#include <memory>
#include <vector>

// AULA - Memoria dinamica moderna
// Em C++ evitamos malloc/free: vector e unique_ptr liberam a memoria sozinhos.
int main()
{
    int quantidade = 5;
    std::vector<int> leituras(quantidade);      // memoria gerenciada

    for (int i = 0; i < quantidade; i++) {
        leituras[i] = (i + 1) * 10;
        std::cout << "leituras[" << i << "] = " << leituras[i] << "\n";
    }

    auto unico = std::make_unique<int>(42);     // ponteiro "inteligente"
    std::cout << "Valor guardado no unique_ptr: " << *unico << "\n";

    return 0;                                   // tudo e liberado automaticamente
}

// EXERCICIOS:
// 1. Mude quantidade para 8.
// 2. Calcule e mostre a soma dos valores do vector.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 08_memoria_dinamica
