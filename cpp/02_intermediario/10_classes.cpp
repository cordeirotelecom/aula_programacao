// Elaborado pelo Prof. Vagner Cordeiro
#include <iostream>
#include <string>

// AULA - Classes (programacao orientada a objetos)
// Uma classe junta dados (atributos) e funcoes (metodos).
// private: so a propria classe acessa; public: qualquer um acessa.
class Led {
public:
    Led(int pino) : pino_(pino), ligado_(false) {}     // construtor

    void ligar()    { ligado_ = true; }
    void desligar() { ligado_ = false; }
    void mostrar() const
    {
        std::cout << "LED do pino " << pino_ << " esta "
                  << (ligado_ ? "ligado" : "desligado") << "\n";
    }

private:
    int pino_;
    bool ligado_;
};

int main()
{
    Led vermelho(13);
    Led verde(12);

    vermelho.ligar();
    vermelho.mostrar();
    verde.mostrar();

    return 0;
}

// EXERCICIOS:
// 1. Adicione o metodo alternar(), que inverte o estado do LED.
// 2. Crie a classe Botao com o metodo pressionado().

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" cpp 10_classes
