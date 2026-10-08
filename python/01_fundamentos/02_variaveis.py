# Elaborado pelo Prof. Vagner Cordeiro
# AULA 2 - Variaveis
# Uma variavel e um nome para um valor. Python descobre o tipo sozinho.

idade = 18             # int: numero inteiro
temperatura = 23.5     # float: numero com virgula
inicial = "A"          # str: texto
ligado = True          # bool: verdadeiro ou falso

# f"..." coloca o valor da variavel dentro do texto.
print(f"Idade: {idade}")
print(f"Temperatura: {temperatura:.1f} graus")
print(f"Inicial: {inicial}")
print(f"Ligado: {ligado}")
print("Tipo de idade:", type(idade).__name__)

# EXERCICIOS:
# 1. Mude a idade e a temperatura e execute novamente.
# 2. Crie uma variavel ano e mostre o seu valor.
# Executar: .\rodar.ps1 02_variaveis.py
