# Elaborado pelo Prof. Vagner Cordeiro
# AULA 8 - Funcoes
# def cria uma funcao: um bloco de codigo com nome, que pode ser reutilizado.

def celsius_para_fahrenheit(c):
    return c * 9 / 5 + 32


def saudacao(nome, ola="Ola"):
    return f"{ola}, {nome}!"


print(celsius_para_fahrenheit(25))
print(saudacao("Ana"))
print(saudacao("Bruno", ola="Bom dia"))

# EXERCICIOS:
# 1. Crie uma funcao area_retangulo(base, altura).
# 2. Crie uma funcao que diga se um numero e par.
# Executar: .\rodar.ps1 08_funcoes.py
