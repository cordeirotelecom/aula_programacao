# Elaborado pelo Prof. Vagner Cordeiro
# APLICACAO - Simula um sensor de temperatura (liga com ESP32 / IoT) e gera JSON.

import json
import random

random.seed(1)  # mesma sequencia a cada execucao, para a aula ser previsivel

for i in range(1, 6):
    leitura = {
        "sensor": "esp32-01",
        "amostra": i,
        "temperatura": round(random.uniform(20, 30), 1),
    }
    alerta = " ALERTA!" if leitura["temperatura"] > 28 else ""
    print(json.dumps(leitura) + alerta)

# EXERCICIOS:
# 1. Mude o limite do alerta.
# 2. Grave as leituras em um arquivo leituras.json.
# Executar: .\rodar.ps1 02_sensor_simulado.py
