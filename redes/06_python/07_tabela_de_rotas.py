# Elaborado pelo Prof. Vagner Cordeiro
# REDES - Simulador de tabela de rotas com "prefixo mais longo" (aula 13).
import ipaddress

TABELA = [
    ("192.168.10.0/24", "direto", "eth0"),
    ("192.168.20.0/24", "direto", "eth1"),
    ("10.0.0.0/8", "192.168.20.254", "eth1"),
    ("10.1.2.0/24", "192.168.20.100", "eth1"),
    ("0.0.0.0/0", "200.10.20.1", "eth2"),
]


def rotear(destino):
    ip = ipaddress.ip_address(destino)
    candidatas = [(ipaddress.ip_network(r), salto, i) for r, salto, i in TABELA if ip in ipaddress.ip_network(r)]
    return max(candidatas, key=lambda c: c[0].prefixlen)  # vence o prefixo mais longo


for destino in ["192.168.20.77", "10.5.5.5", "10.1.2.3", "8.8.8.8"]:
    rede, salto, interface = rotear(destino)
    print(f"{destino:<15} -> rota {str(rede):<16} proximo salto: {salto:<15} saida: {interface}")

# EXERCICIOS:
# 1. Adicione a rota 172.16.0.0/16 via 192.168.10.1 e teste 172.16.5.9.
# 2. Remova a rota padrao (0.0.0.0/0) e teste 8.8.8.8: o que acontece? (Erro proposital.)
# Executar: .\rodar.ps1 07_tabela_de_rotas.py
