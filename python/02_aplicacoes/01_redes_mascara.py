# Elaborado pelo Prof. Vagner Cordeiro
# APLICACAO - Calculo de rede com a biblioteca padrao ipaddress (liga com a pasta redes).

import ipaddress

rede = ipaddress.ip_network("192.168.10.77/26", strict=False)

print("Endereco da rede :", rede.network_address)
print("Broadcast        :", rede.broadcast_address)
print("Mascara          :", rede.netmask)
print("Total de enderecos:", rede.num_addresses)
print("Hosts utilizaveis :", rede.num_addresses - 2)
hosts = list(rede.hosts())
print("Primeiro host    :", hosts[0])
print("Ultimo host      :", hosts[-1])

# EXERCICIOS:
# 1. Troque para 10.0.0.5/24 e compare.
# 2. Divida a rede em sub-redes com rede.subnets(new_prefix=28).
# Executar: .\rodar.ps1 01_redes_mascara.py
