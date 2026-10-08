// Elaborado pelo Prof. Vagner Cordeiro
// Painel de sensores: busca dados a cada 5 s e mostra os estados
// carregando / normal / erro (com ultima leitura guardada).

var INTERVALO_MS = 5000;
var endereco = localStorage.getItem("enderecoDispositivo") || "";
var ultimaLeitura = JSON.parse(localStorage.getItem("ultimaLeitura") || "null");

var el = {
  status: document.getElementById("status"),
  temp: document.getElementById("temperatura"),
  seloTemp: document.getElementById("seloTemp"),
  umi: document.getElementById("umidade"),
  seloUmi: document.getElementById("seloUmi"),
  atualizado: document.getElementById("atualizado"),
  dialogo: document.getElementById("config"),
  campo: document.getElementById("endereco"),
  erroConfig: document.getElementById("erroConfig")
};

function mostrar(dados, desatualizado) {
  el.temp.textContent = dados.temperatura.toFixed(1).replace(".", ",") + " \u00B0C";
  var t = estadoTemperatura(dados.temperatura);
  el.seloTemp.textContent = (t === "Normal" ? "\u2713 " : "\u26A0 ") + t;
  el.seloTemp.className = "selo " + (t === "Normal" ? "ok" : "alerta");

  el.umi.textContent = traduzirUmidade(dados.umidade);
  el.seloUmi.textContent = dados.umidade + "%" + (dados.umidade < 30 ? " \u26A0 Precisa regar" : "");
  el.seloUmi.className = "selo " + (dados.umidade < 30 ? "alerta" : "ok");

  document.querySelector("main").classList.toggle("velho", desatualizado);
}

function mostrarHora() {
  if (ultimaLeitura) {
    el.atualizado.textContent = "Atualizado " + tempoDesde(Date.now(), ultimaLeitura.quando);
  }
}

async function atualizar() {
  el.status.textContent = "Buscando dados...";
  try {
    var dados = await lerDados(endereco, Date.now());
    ultimaLeitura = { dados: dados, quando: Date.now() };
    localStorage.setItem("ultimaLeitura", JSON.stringify(ultimaLeitura));
    mostrar(dados, false);
    el.status.textContent = endereco ? "Conectado" : "Modo exemplo (simulador)";
  } catch (erro) {
    if (ultimaLeitura) {
      mostrar(ultimaLeitura.dados, true);
      el.status.textContent = "Sem conexao com o dispositivo. Mostrando a ultima leitura.";
    } else {
      el.status.textContent = "Sem conexao. Confira se o dispositivo esta ligado e no mesmo Wi-Fi.";
    }
  }
  mostrarHora();
}

document.getElementById("btnAtualizar").addEventListener("click", atualizar);
document.getElementById("btnConfig").addEventListener("click", function () {
  el.campo.value = endereco;
  el.erroConfig.textContent = "";
  el.dialogo.showModal();
});
document.getElementById("btnSalvar").addEventListener("click", function () {
  var novo = normalizarEndereco(el.campo.value);
  if (novo === null) {
    el.erroConfig.textContent = "Endereco invalido. Exemplo: 192.168.0.50";
    return;
  }
  endereco = novo;
  localStorage.setItem("enderecoDispositivo", endereco);
  el.dialogo.close();
  atualizar();
});

if (ultimaLeitura) { mostrar(ultimaLeitura.dados, true); mostrarHora(); }
atualizar();
setInterval(atualizar, INTERVALO_MS);
setInterval(mostrarHora, 1000);

// Service worker: so funciona em localhost ou https (nao em file://)
if ("serviceWorker" in navigator && location.protocol !== "file:") {
  navigator.serviceWorker.register("sw.js").catch(function () {});
}

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\mobile_iot\abrir.ps1" painel_sensores
