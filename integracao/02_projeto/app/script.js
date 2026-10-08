// Elaborado pelo Prof. Vagner Cordeiro
// O APP: le a API (que le o banco) e envia comandos. Como a pagina vem da propria API,
// nao ha problema de CORS e funciona tambem no celular pelo IP do PC.
var DISPOSITIVO = "sala1";
var LIMITE_ALERTA = 30;
var ledAtual = false;

var elTemp = document.getElementById("temperatura");
var elUmid = document.getElementById("umidade");
var elAtual = document.getElementById("atualizacao");
var elAlerta = document.getElementById("alerta");
var elBotao = document.getElementById("botaoLed");
var elMsg = document.getElementById("mensagem");
var elHist = document.getElementById("historico");

function mostrarBotao() {
  elBotao.textContent = "LED: " + (ledAtual ? "LIGADO (toque para desligar)" : "DESLIGADO (toque para ligar)");
  elBotao.className = ledAtual ? "ligado" : "";
}

function textoHora(iso) { return iso ? iso.slice(11, 19) : "--"; }

async function atualizar() {
  try {
    var r = await fetch("/api/dados");
    var lista = await r.json();
    var d = lista.filter(function (x) { return x.dispositivo === DISPOSITIVO; })[0];
    if (!d) { elAtual.textContent = "Aguardando a primeira leitura..."; return; }

    elTemp.textContent = d.temperatura.toFixed(1) + " \u00B0C";
    elUmid.textContent = Math.round(d.umidade) + " %";
    elAtual.textContent = "Ultima leitura: " + textoHora(d.criado_em);
    elAlerta.hidden = d.temperatura <= LIMITE_ALERTA;
    ledAtual = d.led === 1;
    mostrarBotao();

    var h = await (await fetch("/api/historico?limite=8&dispositivo=" + DISPOSITIVO)).json();
    elHist.innerHTML = "";
    h.forEach(function (l) {
      var tr = document.createElement("tr");
      [textoHora(l.criado_em), l.temperatura.toFixed(1) + " \u00B0C", Math.round(l.umidade) + " %"].forEach(function (t) {
        var td = document.createElement("td"); td.textContent = t; tr.appendChild(td);
      });
      elHist.appendChild(tr);
    });
  } catch (e) {
    elAtual.textContent = "Sem conexao com a API. Ela esta rodando?";
  }
}

elBotao.addEventListener("click", async function () {
  elBotao.disabled = true;
  elMsg.textContent = "Enviando comando...";
  try {
    var r = await fetch("/api/comando", {
      method: "POST", headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ dispositivo: DISPOSITIVO, led: !ledAtual })
    });
    elMsg.textContent = r.ok ? "Comando enviado. O botao muda quando o dispositivo confirmar." : "Falha ao enviar.";
  } catch (e) {
    elMsg.textContent = "Falha ao enviar: sem conexao.";
  }
  elBotao.disabled = false;
});

atualizar();
setInterval(atualizar, 2000);
