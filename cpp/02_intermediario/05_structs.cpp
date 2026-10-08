// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>

// AULA - struct em C++
// Em C++ nao precisa escrever "struct" ao declarar a variavel.
struct Sensor {
    int id;
    float temperatura;
    bool ativo;
};

void mostrar(const Sensor &s)
{
    std::cout << "Sensor " << s.id << ": " << s.temperatura << " graus, "
              << (s.ativo ? "ativo" : "inativo") << "\n";
}

int main()
{
    Sensor s1 = {1, 23.5f, true};
    Sensor s2 = {2, 31.0f, false};

    mostrar(s1);
    mostrar(s2);

    s2.ativo = true;
    std::cout << "Sensor 2 foi ativado.\n";
    mostrar(s2);

    return 0;
}

// EXERCICIOS:
// 1. Crie uma struct Aluno com nome (std::string) e nota (float).
// 2. Crie um vector<Sensor> com 3 sensores e mostre todos.

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 05_structs
