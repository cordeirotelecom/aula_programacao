// Elaborado pelo Prof. Vagner Cordeiro
// SIMULADOR DO ESP32: publica leituras por MQTT, igual ao firmware real.
// Assim voce testa todo o sistema SEM ter a placa.
// Topicos: estufa/sala1/dados (publica)  |  estufa/sala1/comando (recebe {"led":true})
const mqtt = require("mqtt");

const SERVIDOR = process.env.MQTT_URL || "mqtt://127.0.0.1:1883";
const DISPOSITIVO = process.env.DISPOSITIVO || "sala1";
const INTERVALO_MS = Number(process.env.INTERVALO_MS || 2000);

let led = false;
let passo = 0;

// Gera valores que sobem e descem; de vez em quando passa de 30 C para gerar ALERTA
function lerSensores() {
  passo++;
  const temperatura = 27 + 5 * Math.sin(passo / 6);
  const umidade = 55 + 20 * Math.cos(passo / 9);
  return { temperatura: Number(temperatura.toFixed(1)), umidade: Math.round(umidade), led };
}

const cliente = mqtt.connect(SERVIDOR);
cliente.on("connect", () => {
  console.log("[simulador] conectado em", SERVIDOR);
  cliente.subscribe(`estufa/${DISPOSITIVO}/comando`);
});
cliente.on("error", (e) => console.error("[simulador] erro:", e.message));
cliente.on("message", (topico, payload) => {
  try {
    const cmd = JSON.parse(payload.toString());
    if (typeof cmd.led === "boolean") {
      led = cmd.led;
      console.log("[simulador] comando recebido: LED", led ? "LIGADO" : "DESLIGADO");
    }
  } catch (e) {
    console.log("[simulador] comando invalido ignorado");
  }
});

setInterval(() => {
  if (!cliente.connected) return;
  const dados = lerSensores();
  cliente.publish(`estufa/${DISPOSITIVO}/dados`, JSON.stringify(dados));
  console.log("[simulador] publicou", JSON.stringify(dados));
}, INTERVALO_MS);
// Executar (PowerShell): cd ".\integracao\02_projeto"; npm run simulador
