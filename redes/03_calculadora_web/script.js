// Elaborado pelo Prof. Vagner Cordeiro
// Liga os botoes da pagina as funcoes de calculo.js

function linha(nome, valor) {
  return "<tr><th>" + nome + "</th><td>" + valor + "</td></tr>";
}

function mostrarCalculo() {
  const erro = document.getElementById("erro");
  const tabela = document.getElementById("resultado");
  const r = calcular(document.getElementById("ip").value, Number(document.getElementById("cidr").value));
  if (!r) {
    erro.textContent = "IP ou CIDR invalido.";
    tabela.innerHTML = "";
    return;
  }
  erro.textContent = "";
  tabela.innerHTML =
    linha("Mascara", numeroParaIp(r.mascara) + " (/" + document.getElementById("cidr").value + ")") +
    linha("Mascara (binario)", paraBinario(r.mascara)) +
    linha("Wildcard", numeroParaIp(r.wildcard)) +
    linha("IP (binario)", paraBinario(r.ip)) +
    linha("Rede (IP AND mascara)", numeroParaIp(r.rede) + "<br>" + paraBinario(r.rede)) +
    linha("Broadcast", numeroParaIp(r.broadcast) + "<br>" + paraBinario(r.broadcast)) +
    linha("Primeiro host", numeroParaIp(r.primeiro)) +
    linha("Ultimo host", numeroParaIp(r.ultimo)) +
    linha("Hosts utilizaveis", r.hosts) +
    linha("Classe", r.classe) +
    linha("Tipo", r.privado ? "Privado" : "Publico/especial");
}

function mostrarDivisao() {
  const tabela = document.getElementById("sub");
  const r = dividir(document.getElementById("ip").value, Number(document.getElementById("cidr").value),
                    Number(document.getElementById("quantidade").value));
  if (!r) {
    tabela.innerHTML = "<tr><td>Nao foi possivel dividir (confira IP, CIDR e quantidade).</td></tr>";
    return;
  }
  let html = "<tr><th>#</th><th>Rede</th><th>Primeiro</th><th>Ultimo</th><th>Broadcast</th></tr>";
  r.lista.forEach(function (s, i) {
    html += "<tr><td>" + (i + 1) + "</td><td>" + numeroParaIp(s.rede) + "/" + r.novoCidr + "</td><td>" +
      numeroParaIp(s.primeiro) + "</td><td>" + numeroParaIp(s.ultimo) + "</td><td>" +
      numeroParaIp(s.broadcast) + "</td></tr>";
  });
  tabela.innerHTML = html;
}

document.getElementById("btnCalcular").addEventListener("click", mostrarCalculo);
document.getElementById("btnDividir").addEventListener("click", mostrarDivisao);
mostrarCalculo();

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\redes\abrir.ps1" calculadora_web
