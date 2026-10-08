# Elaborado pelo Prof. Vagner Cordeiro
# REDES - Gera o plano de enderecamento completo e salva em CSV (aula 16).
import csv
import ipaddress
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from importlib import import_module

vlsm = import_module("02_vlsm").vlsm

pedidos = {"Laboratorio": 60, "Secretaria": 25, "Professores": 12, "Link roteadores": 2}
plano = vlsm("192.168.0.0/24", pedidos)

arquivo = os.path.join(os.path.dirname(os.path.abspath(__file__)), "plano_enderecamento.csv")
with open(arquivo, "w", newline="", encoding="utf-8-sig") as f:  # utf-8-sig: abre certo no Excel
    w = csv.writer(f, delimiter=";")
    w.writerow(["Setor", "Hosts pedidos", "Rede", "Mascara", "Gateway", "Primeiro host", "Ultimo host", "Broadcast", "Hosts uteis"])
    for nome, hosts, r in plano:
        h = list(r.hosts())
        gateway = h[0] if nome != "Link roteadores" else "-"
        w.writerow([nome, hosts, r, r.netmask, gateway, h[0], h[-1], r.broadcast_address, len(h)])

print("Plano gerado:\n")
for nome, hosts, r in plano:
    print(f"  {nome:<16} {str(r):<18} gateway {list(r.hosts())[0]}")
print("\nArquivo salvo em:", arquivo)

# EXERCICIOS:
# 1. Abra o CSV no Excel.
# 2. Mude os setores e acrescente a coluna "VLAN".
# Executar: .\rodar.ps1 06_plano_enderecamento.py
