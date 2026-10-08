// Elaborado pelo Prof. Vagner Cordeiro
// Controle: so mostra "Ligada" depois que o dispositivo CONFIRMAR (estado real).

var endereco = localStorage.getItem("enderecoControle") || "";
var campo = document.getElementById("endereco");
campo.value = endereco;

var elStatus = document.getElementById("status");
var erro = document.getElementById("erro");
var estadoBomba = false;   // a bomba e simulada no app; so o LED existe no firmware

campo.addEventListener("change", function () {
  var novo = normalizarEndereco(campo.value);
  if (novo === null) {
    erro.textContent = "Endereco invalido. Exemplo: 192.168.0.50";
    return;
  }
  erro.textContent = "";
  endereco = novo;
  localStorage.setItem("enderecoControle", endereco);
});

function desenhar(idEstado, idBotao, ligado, nomeLigar, nomeDesligar) {
  var e = document.getElementById(idEstado);
  e.textContent = ligado ? "Ligada" : "Desligada";
  e.classList.toggle("ligado", ligado);
  document.getElementById(idBotao).textContent = ligado ? nomeDesligar : nomeLigar;
}

// Estado "enviando": desabilita o botao ate o dispositivo responder
async function enviar(botao, acao) {
  botao.disabled = true;
  elStatus.textContent = "Enviando comando...";
  erro.textContent = "";
  try {
    await acao();
    elStatus.textContent = "Comando confirmado pelo dispositivo.";
  } catch (e) {
    erro.textContent = "Nao consegui falar com o dispositivo. Confira se ele esta ligado e no mesmo Wi-Fi.";
    elStatus.textContent = "Falhou. O estado mostrado e o ultimo confirmado.";
  } finally {
    botao.disabled = false;
  }
}

var estadoLed = false;
document.getElementById("btnLed").addEventListener("click", function () {
  enviar(this, async function () {
    var r = await comandarLed(endereco, !estadoLed);
    estadoLed = r.led;                               // usa a resposta real
    desenhar("estadoLed", "btnLed", estadoLed, "Ligar lampada", "Desligar lampada");
  });
});

document.getElementById("btnBomba").addEventListener("click", function () {
  var quer = !estadoBomba;
  if (quer && !confirm("Ligar a bomba de irrigacao agora?")) return;   // prevencao de erro
  enviar(this, async function () {
    await new Promise(function (ok) { setTimeout(ok, 600); });         // simula a rede
    estadoBomba = quer;
    desenhar("estadoBomba", "btnBomba", estadoBomba, "Ligar bomba", "Desligar bomba");
  });
});

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\mobile_iot\abrir.ps1" controle_dispositivo
