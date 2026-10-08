// Elaborado pelo Prof. Vagner Cordeiro
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Aluno {
    std::string nome;
    int matricula;
    float nota;
};

// APLICACAO - Cadastro de alunos (vector de structs)
// Os dados ja estao no codigo para simplificar.
int main()
{
    std::vector<Aluno> turma = {
        {"Ana",   101, 8.5f},
        {"Bruno", 102, 5.0f},
        {"Carla", 103, 9.2f}
    };

    turma.push_back({"Davi", 104, 7.0f});     // vector aceita novos alunos

    std::cout << std::left << std::setw(11) << "MATRICULA"
              << std::setw(10) << "NOME" << "NOTA\n";
    for (const Aluno &a : turma) {
        std::cout << std::setw(11) << a.matricula
                  << std::setw(10) << a.nome << a.nota << "\n";
    }

    return 0;
}

// EXERCICIOS:
// 1. Adicione mais um aluno com push_back.
// 2. Mostre o nome do aluno com a maior nota.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 07_cadastro_alunos
