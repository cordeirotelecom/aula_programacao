// Elaborado pelo Prof. Vagner Cordeiro
// API + BANCO DE DADOS + SERVIDOR DO APP (tudo na porta 3000).
//
//   POST /api/leituras   <- Node-RED (ou ingestor.js) envia cada leitura; vira uma linha no SQLite
//   GET  /api/dados      -> ultima leitura de cada dispositivo
//   GET  /api/historico  -> ultimas N leituras (?limite=20&dispositivo=sala1)
//   POST /api/comando    <- o app manda {"dispositivo":"sala1","led":true}; a API publica no MQTT
//   GET  /               -> o aplicativo (pasta app/)
const http = require("node:http");
const fs = require("node:fs");
const path = require("node:path");
const { DatabaseSync } = require("node:sqlite");
const mqtt = require("mqtt");

const PORTA = Number(process.env.PORTA || 3000);
const HOST = process.env.HOST_API || "0.0.0.0";
const MQTT_URL = process.env.MQTT_URL || "mqtt://127.0.0.1:1883";
const ARQUIVO_DB = process.env.ARQUIVO_DB || path.join(__dirname, "dados.db");
const PASTA_APP = path.join(__dirname, "app");

// ---------- Banco de dados SQLite (um arquivo, sem instalar nada) ----------
const banco = new DatabaseSync(ARQUIVO_DB);
banco.exec(`
  CREATE TABLE IF NOT EXISTS leituras (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    dispositivo TEXT NOT NULL,
    temperatura REAL NOT NULL,
    umidade REAL NOT NULL,
    led INTEGER NOT NULL,
    alerta INTEGER NOT NULL DEFAULT 0,
    criado_em TEXT NOT NULL DEFAULT (datetime('now','localtime'))
  )`);
const inserir = banco.prepare(
  "INSERT INTO leituras (dispositivo, temperatura, umidade, led, alerta) VALUES (?, ?, ?, ?, ?)");
const ultimaPorDispositivo = banco.prepare(
  `SELECT * FROM leituras WHERE id IN (SELECT MAX(id) FROM leituras GROUP BY dispositivo)`);
const historico = banco.prepare(
  "SELECT * FROM leituras WHERE dispositivo = ? ORDER BY id DESC LIMIT ?");
// Referencia ao banco: sem isto o Node pode descartar a conexao e os comandos falham
process.on("exit", () => banco.close());

// ---------- MQTT (so para ENVIAR comandos ao dispositivo) ----------
const mqttCliente = mqtt.connect(MQTT_URL);
mqttCliente.on("connect", () => console.log("[api] MQTT conectado"));
mqttCliente.on("error", (e) => console.error("[api] MQTT:", e.message));

// ---------- Funcoes auxiliares ----------
function responder(res, codigo, objeto) {
  res.writeHead(codigo, { "Content-Type": "application/json; charset=utf-8", "Cache-Control": "no-store" });
  res.end(JSON.stringify(objeto));
}

function lerCorpo(req) {
  return new Promise((resolve, reject) => {
    let texto = "";
    req.on("data", (pedaco) => {
      texto += pedaco;
      if (texto.length > 10_000) { reject(new Error("corpo grande demais")); req.destroy(); }
    });
    req.on("end", () => { try { resolve(JSON.parse(texto || "{}")); } catch (e) { reject(new Error("JSON invalido")); } });
  });
}

// Nome do dispositivo: so letras, numeros, _ e - (evita topicos MQTT estranhos)
const nomeValido = (n) => typeof n === "string" && /^[A-Za-z0-9_-]{1,32}$/.test(n);
const numeroValido = (v) => typeof v === "number" && Number.isFinite(v);

const TIPOS = { ".html": "text/html; charset=utf-8", ".css": "text/css", ".js": "text/javascript", ".json": "application/json", ".svg": "image/svg+xml" };

function servirArquivo(req, res) {
  const url = new URL(req.url, "http://x");
  let caminho = path.normalize(path.join(PASTA_APP, decodeURIComponent(url.pathname)));
  if (!caminho.startsWith(PASTA_APP)) return responder(res, 403, { erro: "proibido" });
  if (url.pathname === "/") caminho = path.join(PASTA_APP, "index.html");
  fs.readFile(caminho, (erro, dados) => {
    if (erro) return responder(res, 404, { erro: "nao encontrado" });
    res.writeHead(200, { "Content-Type": TIPOS[path.extname(caminho)] || "application/octet-stream" });
    res.end(dados);
  });
}

// ---------- Rotas ----------
const servidor = http.createServer(async (req, res) => {
  const url = new URL(req.url, "http://x");
  try {
    if (req.method === "POST" && url.pathname === "/api/leituras") {
      const d = await lerCorpo(req);
      if (!nomeValido(d.dispositivo) || !numeroValido(d.temperatura) || !numeroValido(d.umidade)) {
        return responder(res, 400, { erro: "campos obrigatorios: dispositivo, temperatura, umidade (numeros)" });
      }
      inserir.run(d.dispositivo, d.temperatura, d.umidade, d.led ? 1 : 0, d.alerta ? 1 : 0);
      return responder(res, 201, { ok: true });
    }
    if (req.method === "GET" && url.pathname === "/api/dados") {
      return responder(res, 200, ultimaPorDispositivo.all());
    }
    if (req.method === "GET" && url.pathname === "/api/historico") {
      const limite = Math.min(Math.max(parseInt(url.searchParams.get("limite") || "20", 10) || 20, 1), 500);
      const disp = url.searchParams.get("dispositivo") || "sala1";
      if (!nomeValido(disp)) return responder(res, 400, { erro: "dispositivo invalido" });
      return responder(res, 200, historico.all(disp, limite));
    }
    if (req.method === "POST" && url.pathname === "/api/comando") {
      const d = await lerCorpo(req);
      if (!nomeValido(d.dispositivo) || typeof d.led !== "boolean") {
        return responder(res, 400, { erro: "envie {dispositivo, led:true|false}" });
      }
      mqttCliente.publish(`estufa/${d.dispositivo}/comando`, JSON.stringify({ led: d.led }));
      return responder(res, 202, { ok: true, enviado: { led: d.led } });
    }
    if (req.method === "GET") return servirArquivo(req, res);
    responder(res, 405, { erro: "metodo nao permitido" });
  } catch (e) {
    responder(res, 400, { erro: e.message });
  }
});

servidor.listen(PORTA, HOST, () => {
  console.log(`[api] pronta em http://localhost:${PORTA}/  (banco: ${ARQUIVO_DB})`);
});
servidor.on("error", (e) => {
  console.error("[api] erro:", e.code === "EADDRINUSE" ? `porta ${PORTA} em uso` : e.message);
  process.exit(1);
});
// Executar (PowerShell): cd ".\integracao\02_projeto"; npm run api
