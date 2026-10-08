// Elaborado pelo Prof. Vagner Cordeiro
// Logica compartilhada dos projetos mobile (sem DOM, testavel no Node).

// Converte a umidade do solo (0-100%) em palavra
function traduzirUmidade(percentual) {
  if (percentual < 30) return "Seco";
  if (percentual <= 70) return "Ideal";
  return "Encharcado";
}

function estadoTemperatura(celsius) {
  if (celsius < 18) return "Frio";
  if (celsius <= 30) return "Normal";
  return "Quente";
}

// "agora", "ha 5 s", "ha 2 min", "ha 3 h"
function tempoDesde(agoraMs, antesMs) {
  var s = Math.max(0, Math.round((agoraMs - antesMs) / 1000));
  if (s < 5) return "agora";
  if (s < 60) return "ha " + s + " s";
  if (s < 3600) return "ha " + Math.floor(s / 60) + " min";
  return "ha " + Math.floor(s / 3600) + " h";
}

// Normaliza o que o usuario digitou: "192.168.0.50" -> "http://192.168.0.50"
function normalizarEndereco(texto) {
  var t = (texto || "").trim().replace(/\/+$/, "");
  if (t === "") return "";
  if (!/^https?:\/\//i.test(t)) t = "http://" + t;
  return /^https?:\/\/[A-Za-z0-9.\-]+(:\d{1,5})?$/.test(t) ? t : null;
}

// Gera leituras falsas para treinar sem o ESP32
function gerarDadosSimulados(agoraMs) {
  var onda = Math.sin(agoraMs / 20000);
  return {
    temperatura: Math.round((26 + 5 * onda) * 10) / 10,
    umidade: Math.round(50 + 40 * Math.cos(agoraMs / 30000)),
    led: false
  };
}

// fetch com limite de tempo (o celular pode ficar sem rede)
function buscarComTempo(url, opcoes, limiteMs) {
  var controle = new AbortController();
  var timer = setTimeout(function () { controle.abort(); }, limiteMs);
  var config = Object.assign({}, opcoes, { signal: controle.signal });
  return fetch(url, config).finally(function () { clearTimeout(timer); });
}

// Le {temperatura, umidade, led}. Sem endereco usa o simulador.
async function lerDados(endereco, agoraMs) {
  if (!endereco) return gerarDadosSimulados(agoraMs);
  var resposta = await buscarComTempo(endereco + "/dados", {}, 4000);
  if (!resposta.ok) throw new Error("HTTP " + resposta.status);
  return resposta.json();
}

// Liga/desliga o LED. Devolve o estado REAL informado pelo dispositivo.
async function comandarLed(endereco, ligado) {
  if (!endereco) return { led: ligado };
  var resposta = await buscarComTempo(endereco + "/led?estado=" + (ligado ? 1 : 0), {}, 4000);
  if (!resposta.ok) throw new Error("HTTP " + resposta.status);
  return resposta.json();
}

if (typeof module !== "undefined") {
  module.exports = { traduzirUmidade, estadoTemperatura, tempoDesde, normalizarEndereco, gerarDadosSimulados, lerDados, comandarLed };
}

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\mobile_iot\abrir.ps1" painel_sensores
