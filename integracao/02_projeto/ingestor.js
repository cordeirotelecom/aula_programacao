// Elaborado pelo Prof. Vagner Cordeiro
// INGESTOR (alternativa ao Node-RED): faz exatamente o mesmo trabalho em codigo.
//   1) assina estufa/+/dados   2) calcula alerta   3) envia para a API gravar no banco
// Use se nao quiser instalar/abrir o Node-RED. NAO rode junto com o Node-RED (duplicaria os dados).
const mqtt = require("mqtt");

const MQTT_URL = process.env.MQTT_URL || "mqtt://127.0.0.1:1883";
const API_URL = process.env.API_URL || "http://127.0.0.1:3000";
const LIMITE_TEMPERATURA = 30;

const cliente = mqtt.connect(MQTT_URL);
cliente.on("connect", () => {
  console.log("[ingestor] conectado; assinando estufa/+/dados");
  cliente.subscribe("estufa/+/dados");
});
cliente.on("error", (e) => console.error("[ingestor] erro:", e.message));

cliente.on("message", async (topico, payload) => {
  const dispositivo = topico.split("/")[1]; // estufa/<dispositivo>/dados
  let d;
  try { d = JSON.parse(payload.toString()); } catch (e) { return console.log("[ingestor] JSON invalido ignorado"); }

  const alerta = d.temperatura > LIMITE_TEMPERATURA;
  const registro = { dispositivo, temperatura: d.temperatura, umidade: d.umidade, led: !!d.led, alerta };
  try {
    const r = await fetch(`${API_URL}/api/leituras`, {
      method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify(registro) });
    console.log("[ingestor] gravado", r.status, JSON.stringify(registro));
    if (alerta) cliente.publish("estufa/alerta", JSON.stringify({ dispositivo, temperatura: d.temperatura }));
  } catch (e) {
    console.error("[ingestor] API fora do ar:", e.message);
  }
});
// Executar (PowerShell): cd ".\integracao\02_projeto"; npm run ingestor
