# Elaborado pelo Prof. Vagner Cordeiro
# REDES - Duas maquinas estao na mesma rede? (aula 11)
# Regra: IP AND mascara de cada uma; se o resultado for igual, estao na mesma rede.
import ipaddress
import sys


def mesma_rede(ip1, ip2, cidr):
    r1 = ipaddress.ip_interface(f"{ip1}/{cidr}").network
    r2 = ipaddress.ip_interface(f"{ip2}/{cidr}").network
    return r1 == r2, r1, r2


casos = [("192.168.1.10", "192.168.1.200", 24),
         ("192.168.1.10", "192.168.2.20", 24),
         ("192.168.1.10", "192.168.2.20", 22),
         ("10.0.0.5", "10.0.255.6", 16)]
if len(sys.argv) == 4:  # uso: 01_mesma_rede.py IP1 IP2 CIDR
    casos = [(sys.argv[1], sys.argv[2], int(sys.argv[3]))]

for ip1, ip2, cidr in casos:
    igual, r1, r2 = mesma_rede(ip1, ip2, cidr)
    print(f"{ip1} e {ip2} com /{cidr}")
    print(f"   rede 1 = {r1}   rede 2 = {r2}")
    print("   =>", "MESMA rede: conversam direto" if igual else "redes DIFERENTES: precisam de um roteador")

# EXERCICIOS:
# 1. Rode com seus proprios valores: .\rodar.ps1 01_mesma_rede.py   (veja o codigo para argumentos)
# 2. Por que /22 junta 192.168.1.x e 192.168.2.x?
# Executar: .\rodar.ps1 01_mesma_rede.py
