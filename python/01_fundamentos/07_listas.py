# Elaborado pelo Prof. Vagner Cordeiro
# AULA 7 - Listas (o "vetor" do Python)

sensores = ["temperatura", "umidade", "luz"]
sensores.append("pressao")      # adiciona no final

print("Primeiro:", sensores[0])
print("Ultimo:", sensores[-1])
print("Quantidade:", len(sensores))

for s in sensores:
    print("-", s)

leituras = [21.5, 22.0, 23.1, 22.4]
print("Media:", sum(leituras) / len(leituras))
print("Maior:", max(leituras))

# EXERCICIOS:
# 1. Adicione um novo sensor e mostre a lista.
# 2. Mostre a menor leitura com min().
# Executar: .\rodar.ps1 07_listas.py
