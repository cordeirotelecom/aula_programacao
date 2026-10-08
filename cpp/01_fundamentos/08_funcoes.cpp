// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// Uma funcao agrupa comandos com um nome.
// Esta recebe um numero e devolve o dobro dele.
int dobrar(int numero)
{
    return numero * 2;
}

// AULA 8 - Funcoes
// Funcoes evitam repetir codigo e deixam o programa organizado.
int main()
{
    int resultado = dobrar(5);

    std::cout << "O dobro de 5 e " << resultado << std::endl;
    std::cout << "O dobro de 12 e " << dobrar(12) << std::endl;

    return 0;
}

// EXERCICIOS:
//  1. Crie a funcao triplicar e use-a no main.
//  2. Crie uma funcao somar(a, b) que devolve a soma dos dois numeros.
// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 08_funcoes
