# Elaborado pelo Prof. Vagner Cordeiro
# REDES - VLSM: divide uma rede em sub-redes de tamanhos diferentes (aula 7 e 16).
import ipaddress
import math


def vlsm(rede_base, pedidos):
    """pedidos = {nome: hosts}. Atende do maior para o menor, sem sobrepor."""
    base = ipaddress.ip_network(rede_base)
    cursor = int(base.network_address)
    plano = []
    for nome, hosts in sorted(pedidos.items(), key=lambda p: -p[1]):
        bits = max(2, math.ceil(math.log2(hosts + 2)))  # hosts + rede + broadcast
        rede = ipaddress.ip_network((cursor, 32 - bits))
        if rede.broadcast_address > base.broadcast_address:
            raise ValueError(f"Nao ha espaco em {base} para '{nome}'")
        plano.append((nome, hosts, rede))
        cursor = int(rede.broadcast_address) + 1
    return plano


if __name__ == "__main__":
    pedidos = {"Laboratorio": 60, "Secretaria": 25, "Professores": 12, "Link roteadores": 2}
    print(f"{'Setor':<16}{'Hosts':>6}  {'Rede':<18}{'Mascara':<16}{'Faixa de hosts':<32}Broadcast")
    for nome, hosts, r in vlsm("192.168.0.0/24", pedidos):
        h = list(r.hosts())
        print(f"{nome:<16}{hosts:>6}  {str(r):<18}{str(r.netmask):<16}{str(h[0]) + ' - ' + str(h[-1]):<32}{r.broadcast_address}")

# EXERCICIOS:
# 1. Troque os pedidos pelos da aula 16 (10.10.0.0/22 com 300, 120, 50 e 10).
# 2. O que acontece se pedir 400 hosts em uma /24? (O erro e proposital.)
# Executar: .\rodar.ps1 02_vlsm.py
