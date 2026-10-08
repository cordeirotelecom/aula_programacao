# Elaborado pelo Prof. Vagner Cordeiro
# REDES - Cliente e servidor TCP (sockets) no mesmo programa, so no seu PC (aula 8).
# O servidor escuta uma porta (como um site escuta a 80); o cliente conecta e conversa.
import socket
import threading

ENDERECO = "127.0.0.1"
pronto = threading.Event()
porta_escolhida = []


def servidor():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((ENDERECO, 0))            # porta 0 = o sistema escolhe uma livre
        s.listen()
        porta_escolhida.append(s.getsockname()[1])
        pronto.set()
        conexao, origem = s.accept()
        with conexao:
            print(f"[servidor] conexao recebida de {origem}")
            while True:
                dados = conexao.recv(1024)
                if not dados:
                    break
                texto = dados.decode()
                print(f"[servidor] recebi: {texto!r}")
                conexao.sendall(f"ECO: {texto.upper()}".encode())


t = threading.Thread(target=servidor)
t.start()
pronto.wait()
print(f"[cliente] conectando em {ENDERECO}:{porta_escolhida[0]}")

with socket.create_connection((ENDERECO, porta_escolhida[0])) as c:
    for msg in ["ola rede", "temperatura=24.5", "tchau"]:
        c.sendall(msg.encode())
        print("[cliente] resposta:", c.recv(1024).decode())
t.join()

# EXERCICIOS:
# 1. Faca o servidor responder "OK" em vez de ECO.
# 2. Qual a relacao com MQTT (porta 1883) usado no ESP32? Pesquise.
# Executar: .\rodar.ps1 08_servidor_cliente_tcp.py
