// Elaborado pelo Prof. Vagner Cordeiro
// BROKER MQTT: o "correio" do sistema. Recebe mensagens e entrega a quem assinou o topico.
// ESP32 e simulador publicam; Node-RED e API assinam. Porta padrao do MQTT: 1883.
const net = require("node:net");

async function main() {
  const { Aedes } = await import("aedes"); // aedes e um modulo moderno (ESM)
  const aedes = await Aedes.createBroker();
  const servidor = net.createServer(aedes.handle);

  servidor.listen(1883, process.env.MQTT_HOST || "0.0.0.0", () => {
    console.log("[broker] MQTT ouvindo na porta 1883");
  });
  servidor.on("error", (e) => {
    console.error("[broker] erro:", e.code === "EADDRINUSE" ? "porta 1883 ja esta em uso (outro broker rodando?)" : e.message);
    process.exit(1);
  });

  aedes.on("client", (c) => console.log("[broker] conectou:", c.id));
  aedes.on("clientDisconnect", (c) => console.log("[broker] saiu:", c.id));
  aedes.on("publish", (p, c) => {
    if (c && !p.topic.startsWith("$SYS")) console.log("[broker] " + p.topic + " <- " + p.payload.toString());
  });
}

main();
// Executar (PowerShell): cd ".\integracao\02_projeto"; npm run broker
