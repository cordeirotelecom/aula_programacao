# Elaborado pelo Prof. Vagner Cordeiro
# REDES - Scanner de portas SOMENTE no proprio computador (127.0.0.1). (aula 15)
# Mostra como o TCP funciona: connect_ex retorna 0 quando ha um servico escutando.
# NAO use em redes de terceiros: varredura sem autorizacao pode ser crime.
import socket
import threading

ALVO = "127.0.0.1"
PORTAS = {21: "FTP", 22: "SSH", 53: "DNS", 80: "HTTP", 135: "RPC (Windows)",
          139: "NetBIOS", 443: "HTTPS", 445: "SMB (Windows)", 1883: "MQTT",
          3306: "MySQL", 3389: "Area de trabalho remota", 8080: "HTTP alternativo"}


def testar(porta):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.settimeout(0.5)
        return s.connect_ex((ALVO, porta)) == 0


# Abrimos uma porta de proposito para voce ver o scanner encontra-la.
servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
servidor.bind((ALVO, 0))
servidor.listen()
porta_demo = servidor.getsockname()[1]
PORTAS[porta_demo] = "<< servidor criado por este programa >>"

print(f"Varrendo {ALVO} ({len(PORTAS)} portas)...\n")
resultado = {}


def tarefa(p):
    resultado[p] = testar(p)


threads = [threading.Thread(target=tarefa, args=(p,)) for p in PORTAS]
for t in threads:
    t.start()
for t in threads:
    t.join()

for porta in sorted(PORTAS):
    estado = "ABERTA " if resultado[porta] else "fechada"
    print(f"  {porta:>5}  {estado}  {PORTAS[porta]}")
servidor.close()

# EXERCICIOS:
# 1. Quais portas abertas voce nao esperava? Pesquise para que servem.
# 2. Adicione a porta 5000 na lista e rode de novo.
# Executar: .\rodar.ps1 03_scanner_portas.py
