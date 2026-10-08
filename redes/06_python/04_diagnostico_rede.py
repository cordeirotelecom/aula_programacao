# Elaborado pelo Prof. Vagner Cordeiro
# REDES - Diagnostico automatico: passos 1 a 3 da aula 17.
import platform
import socket
import subprocess


def ping(destino):
    opcao = "-n" if platform.system() == "Windows" else "-c"
    r = subprocess.run(["ping", opcao, "2", destino], capture_output=True, text=True)
    return r.returncode == 0


def meu_ip():
    # Nao envia nada: so descobre qual interface o sistema usaria para sair.
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]
    except OSError:
        return None
    finally:
        s.close()


print("Nome do computador:", socket.gethostname())
ip = meu_ip()
print("Meu IP na rede    :", ip or "(sem rede)")

testes = [("1. Placa de rede (127.0.0.1)", "127.0.0.1"),
          ("2. Internet por IP (8.8.8.8)", "8.8.8.8")]
for nome, alvo in testes:
    print(f"{nome:<32}", "OK" if ping(alvo) else "FALHOU")

try:
    ipdns = socket.gethostbyname("google.com")
    print(f"3. DNS (google.com)             OK -> {ipdns}")
except OSError:
    print("3. DNS (google.com)             FALHOU")

# EXERCICIOS:
# 1. Adicione o ping para o seu gateway (veja ipconfig).
# 2. Troque google.com por outro site.
# Executar: .\rodar.ps1 04_diagnostico_rede.py
