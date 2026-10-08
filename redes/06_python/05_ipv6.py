# Elaborado pelo Prof. Vagner Cordeiro
# REDES - IPv6: expandir, abreviar e classificar enderecos (aula 14).
import ipaddress

enderecos = ["2001:0db8:0000:0000:00a0:0000:0000:0005", "::1", "fe80::1c2d:3e4f:5a6b:7c8d",
             "fc00::1", "2001:db8::1", "ff02::1"]

for texto in enderecos:
    ip = ipaddress.IPv6Address(texto)
    if ip.is_loopback:
        tipo = "loopback"
    elif ip.is_link_local:
        tipo = "link-local (so rede local)"
    elif ip.is_multicast:
        tipo = "multicast"
    elif ip.is_private:
        tipo = "privado / documentacao"
    else:
        tipo = "global (publico)"
    print(f"Original  : {texto}")
    print(f"Completo  : {ip.exploded}")
    print(f"Abreviado : {ip.compressed}")
    print(f"Tipo      : {tipo}\n")

# EXERCICIOS:
# 1. Teste os enderecos do exercicio da aula 14.
# 2. Quantos enderecos tem um prefixo /64? Use ipaddress.ip_network("2001:db8::/64").num_addresses
# Executar: .\rodar.ps1 05_ipv6.py
