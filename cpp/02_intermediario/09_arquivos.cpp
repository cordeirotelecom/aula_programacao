// Elaborado pelo Prof. Vagner Cordeiro
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

// AULA - Arquivos com fstream
// ofstream escreve, ifstream le. O arquivo fecha sozinho ao sair do bloco.
int main()
{
    const std::string nome_arquivo = "dados_teste_cpp.txt";

    {
        std::ofstream saida(nome_arquivo);
        if (!saida) {
            std::cout << "Nao foi possivel criar o arquivo.\n";
            return 1;
        }
        saida << "Temperatura: 24\n";
        saida << "Umidade: 60\n";
    }

    std::ifstream entrada(nome_arquivo);
    std::string linha;
    while (std::getline(entrada, linha)) {
        std::cout << "Lido: " << linha << "\n";
    }
    entrada.close();

    std::remove(nome_arquivo.c_str());      // apaga o arquivo de teste
    return 0;
}

// EXERCICIOS:
// 1. Escreva uma terceira linha: "Pressao: 1013".
// 2. Comente a linha remove(...) e abra o arquivo no Bloco de Notas.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 09_arquivos
