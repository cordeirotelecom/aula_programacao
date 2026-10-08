// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA 8 - Estados com switch
// Muitos sistemas embarcados funcionam por estados.
// Cada numero abaixo representa um estado do semaforo.
int main()
{
    int estado = 2; // 0 = vermelho, 1 = amarelo, 2 = verde

    switch (estado) {
    case 0:
        std::cout << "Semaforo vermelho" << std::endl;
        break;
    case 1:
        std::cout << "Semaforo amarelo" << std::endl;
        break;
    case 2:
        std::cout << "Semaforo verde" << std::endl;
        break;
    default:
        std::cout << "Estado desconhecido" << std::endl;
    }

    return 0;
}

// EXERCICIOS:
//  1. Teste os estados 0, 1, 2 e 5.
//  2. Use um for para mostrar a sequencia 0, 1, 2 repetida duas vezes.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 08_maquina_estados
