// Elaborado pelo Prof. Vagner Cordeiro
// Laboratorio interativo de redes. Usa as funcoes de ../03_calculadora_web/calculo.js
"use strict";

var $ = function (id) { return document.getElementById(id); };
var ip2n = ipParaNumero, n2ip = numeroParaIp;

function linhaTab(nome, valor) { return "<tr><td>" + nome + "</td><td class='mono'>" + valor + "</td></tr>"; }

// ---------- abas ----------
var paineis = document.querySelectorAll(".painel");
paineis.forEach(function (p, i) {
  var b = document.createElement("button");
  b.textContent = p.dataset.titulo;
  b.onclick = function () { mostrarAba(i); };
  $("abas").appendChild(b);
});
function mostrarAba(i) {
  paineis.forEach(function (p, j) { p.classList.toggle("on", i === j); });
  $("abas").querySelectorAll("button").forEach(function (b, j) { b.classList.toggle("on", i === j); });
}
mostrarAba(0);

// ---------- 1. binario ----------
var valores = [128, 64, 32, 16, 8, 4, 2, 1], bitsEl = [];
valores.forEach(function (v, i) {
  var d = document.createElement("div");
  d.className = "bit"; d.innerHTML = "0<small>" + v + "</small>";
  d.onclick = function () { d.classList.toggle("on"); atualizarBits(); };
  $("bits").appendChild(d); bitsEl.push(d);
});
function atualizarBits() {
  var soma = 0;
  bitsEl.forEach(function (d, i) {
    var lig = d.classList.contains("on");
    d.firstChild.nodeValue = lig ? "1" : "0";
    if (lig) soma += valores[i];
  });
  $("bin-dec").textContent = soma;
}
$("bin-zero").onclick = function () { bitsEl.forEach(function (d) { d.classList.remove("on"); }); atualizarBits(); };
$("bin-tudo").onclick = function () { bitsEl.forEach(function (d) { d.classList.add("on"); }); atualizarBits(); };
function atualizarIpBin() {
  var n = ip2n($("bin-ip").value);
  $("bin-saida").textContent = n === null ? "IP invalido" : paraBinario(n);
}
$("bin-ip").oninput = atualizarIpBin; atualizarIpBin();

// ---------- 2. calculadora ----------
function calcularTela() {
  var cidr = Number($("c-cidr").value), r = calcular($("c-ip").value, cidr);
  if (!r) { $("c-erro").textContent = "IP ou CIDR invalido."; $("c-res").innerHTML = ""; $("c-passos").innerHTML = ""; return; }
  $("c-erro").textContent = "";
  $("c-res").innerHTML =
    linhaTab("Mascara", n2ip(r.mascara) + " (/" + cidr + ")") +
    linhaTab("Mascara binaria", paraBinario(r.mascara)) +
    linhaTab("IP binario", paraBinario(r.ip)) +
    linhaTab("Rede (IP AND mascara)", n2ip(r.rede)) +
    linhaTab("Broadcast", n2ip(r.broadcast)) +
    linhaTab("Primeiro host", n2ip(r.primeiro)) +
    linhaTab("Ultimo host", n2ip(r.ultimo)) +
    linhaTab("Hosts uteis", r.hosts.toLocaleString("pt-BR")) +
    linhaTab("Classe / tipo", r.classe + " / " + (r.privado ? "privado" : "publico"));
  var bitsHost = 32 - cidr;
  $("c-passos").innerHTML =
    "<li>/" + cidr + " = " + cidr + " bits de rede e <b>" + bitsHost + " bits de host</b>.</li>" +
    "<li>A mascara tem " + cidr + " bits 1 seguidos de " + bitsHost + " bits 0: <span class='mono'>" + paraBinario(r.mascara) + "</span> = " + n2ip(r.mascara) + ".</li>" +
    "<li>Rede = IP <b>AND</b> mascara (bit a bit): zera os bits de host. Resultado: " + n2ip(r.rede) + ".</li>" +
    "<li>Broadcast = rede com <b>todos os bits de host em 1</b>: " + n2ip(r.broadcast) + ".</li>" +
    "<li>Hosts = 2<sup>" + bitsHost + "</sup> - 2 = " + r.hosts.toLocaleString("pt-BR") + " (menos o endereco de rede e o de broadcast).</li>";
}
$("c-btn").onclick = calcularTela; calcularTela();

// ---------- 3. mesma rede e classificar ----------
$("m-btn").onclick = function () {
  var c = Number($("m-cidr").value), a = calcular($("m-ip1").value, c), b = calcular($("m-ip2").value, c);
  if (!a || !b) { $("m-res").innerHTML = "<span class='erro'>IP ou CIDR invalido.</span>"; return; }
  var igual = a.rede === b.rede;
  $("m-res").innerHTML = "Rede do PC 1: <b>" + n2ip(a.rede) + "/" + c + "</b><br>Rede do PC 2: <b>" + n2ip(b.rede) + "/" + c + "</b><br>" +
    (igual ? "<span class='ok'>Mesma rede: conversam direto (via switch).</span>"
           : "<span class='erro'>Redes diferentes: precisam de um roteador/gateway.</span>");
};
$("k-btn").onclick = function () {
  var n = ip2n($("k-ip").value);
  if (n === null) { $("k-res").innerHTML = "<span class='erro'>IP invalido.</span>"; return; }
  var a = n >>> 24, b = (n >>> 16) & 255, esp = "publico";
  if (ehPrivado(n)) esp = "privado";
  if (a === 127) esp = "loopback (a propria maquina)";
  if (a === 169 && b === 254) esp = "APIPA (DHCP falhou)";
  $("k-res").innerHTML = "Classe: <b>" + classeDoIp(n) + "</b><br>Tipo: <b>" + esp + "</b>";
};
$("k-btn").onclick();

// ---------- 4. VLSM ----------
var ultimoPlano = [];
function vlsm(redeTexto, cidr, pedidos) {
  var base = (ip2n(redeTexto) & mascaraDeCidr(cidr)) >>> 0, fim = base + 2 ** (32 - cidr) - 1, cursor = base, plano = [];
  pedidos.sort(function (x, y) { return y.hosts - x.hosts; }).forEach(function (p) {
    var bits = 2; while (2 ** bits < p.hosts + 2) bits++;
    var tam = 2 ** bits;
    if (cursor + tam - 1 > fim) throw new Error("Nao ha espaco para '" + p.nome + "' (" + p.hosts + " hosts).");
    plano.push({ nome: p.nome, hosts: p.hosts, rede: cursor, cidr: 32 - bits, broadcast: cursor + tam - 1 });
    cursor += tam;
  });
  return plano;
}
$("v-btn").onclick = function () {
  $("v-erro").textContent = ""; $("v-res").innerHTML = ""; ultimoPlano = [];
  try {
    var cidr = Number($("v-cidr").value);
    if (ip2n($("v-rede").value) === null || !(cidr >= 0 && cidr <= 30)) throw new Error("Rede ou CIDR invalido.");
    var pedidos = $("v-setores").value.split("\n").filter(function (l) { return l.trim(); }).map(function (l) {
      var p = l.split(":"), h = Number(p[1]);
      if (p.length !== 2 || !(h >= 1)) throw new Error("Linha invalida: '" + l + "' (use nome:hosts)");
      return { nome: p[0].trim(), hosts: h };
    });
    ultimoPlano = vlsm($("v-rede").value, cidr, pedidos);
    $("v-res").innerHTML = "<tr><th>Setor</th><th>Hosts</th><th>Rede</th><th>Mascara</th><th>Faixa</th><th>Broadcast</th></tr>" +
      ultimoPlano.map(function (s) {
        var m = mascaraDeCidr(s.cidr);
        return "<tr><td>" + s.nome + "</td><td>" + s.hosts + "</td><td>" + n2ip(s.rede) + "/" + s.cidr + "</td><td>" + n2ip(m) + "</td><td>" +
          n2ip(s.rede + 1) + " - " + n2ip(s.broadcast - 1) + "</td><td>" + n2ip(s.broadcast) + "</td></tr>";
      }).join("");
  } catch (e) { $("v-erro").textContent = e.message; }
};
$("v-csv").onclick = function () {
  if (!ultimoPlano.length) { $("v-btn").onclick(); }
  if (!ultimoPlano.length) return;
  var csv = "\ufeffSetor;Hosts;Rede;Mascara;Primeiro;Ultimo;Broadcast\r\n" + ultimoPlano.map(function (s) {
    return [s.nome, s.hosts, n2ip(s.rede) + "/" + s.cidr, n2ip(mascaraDeCidr(s.cidr)), n2ip(s.rede + 1), n2ip(s.broadcast - 1), n2ip(s.broadcast)].join(";");
  }).join("\r\n");
  var a = document.createElement("a");
  a.href = URL.createObjectURL(new Blob([csv], { type: "text/csv;charset=utf-8" }));
  a.download = "plano_enderecamento.csv"; a.click();
};
$("v-btn").onclick();

// ---------- 5. rotas ----------
$("r-btn").onclick = function () {
  var dest = ip2n($("r-dest").value);
  if (dest === null) { $("r-res").innerHTML = "<span class='erro'>Destino invalido.</span>"; return; }
  var melhor = null, linhas = [];
  $("r-tab").value.split("\n").forEach(function (l) {
    var p = l.trim().split(/\s+/);
    if (p.length < 2) return;
    var rc = p[0].split("/"), rede = ip2n(rc[0]), c = Number(rc[1]);
    if (rede === null || !(c >= 0 && c <= 32)) { linhas.push("<li class='erro'>Linha invalida: " + l + "</li>"); return; }
    var combina = ((dest & mascaraDeCidr(c)) >>> 0) === ((rede & mascaraDeCidr(c)) >>> 0);
    linhas.push("<li>" + p[0] + " via " + p[1] + ": " + (combina ? "<b class='ok'>combina</b>" : "nao combina") + "</li>");
    if (combina && (!melhor || c > melhor.c)) melhor = { rota: p[0], salto: p[1], c: c };
  });
  $("r-res").innerHTML = "<ul>" + linhas.join("") + "</ul>" +
    (melhor ? "<p>Vence o <b>prefixo mais longo</b> (/" + melhor.c + "): rota <b>" + melhor.rota + "</b>, proximo salto <b>" + melhor.salto + "</b>.</p>"
            : "<p class='erro'>Nenhuma rota combina: o pacote e descartado (falta rota padrao 0.0.0.0/0).</p>");
};
$("r-btn").onclick();

// ---------- 6. quiz ----------
var pergunta = null, acertos = 0, total = 0;
function aleat(a, b) { return a + Math.floor(Math.random() * (b - a + 1)); }
function novaPergunta() {
  var base = [10, 172, 192][aleat(0, 2)], seg = base === 10 ? aleat(0, 255) : base === 172 ? aleat(16, 31) : 168;
  var cidr = aleat(base === 10 ? 8 : 16, 29), ip = base + "." + seg + "." + aleat(0, 255) + "." + aleat(1, 254);
  var r = calcular(ip, cidr), tipo = aleat(0, 3), txt, resp, dica;
  if (tipo === 0) { txt = "Qual o endereco de REDE de " + ip + "/" + cidr + "?"; resp = n2ip(r.rede); dica = "IP AND mascara (" + n2ip(r.mascara) + ")."; }
  else if (tipo === 1) { txt = "Qual o BROADCAST de " + ip + "/" + cidr + "?"; resp = n2ip(r.broadcast); dica = "Todos os bits de host em 1."; }
  else if (tipo === 2) { txt = "Quantos HOSTS uteis tem uma rede /" + cidr + "?"; resp = String(r.hosts); dica = "2^" + (32 - cidr) + " - 2."; }
  else { txt = "Qual a MASCARA de /" + cidr + "?"; resp = n2ip(r.mascara); dica = cidr + " bits 1 seguidos de zeros."; }
  pergunta = { txt: txt, resp: resp, dica: dica, respondida: false };
  $("q-pergunta").textContent = txt; $("q-resp").value = ""; $("q-fb").textContent = ""; $("q-resp").focus();
}
function responder() {
  if (!pergunta || pergunta.respondida) return;
  pergunta.respondida = true; total++;
  var ok = $("q-resp").value.replace(/\s/g, "") === pergunta.resp;
  if (ok) acertos++;
  $("q-fb").innerHTML = ok ? "<span class='ok'>Correto!</span>" : "<span class='erro'>Resposta certa: " + pergunta.resp + "</span> <small>(" + pergunta.dica + ")</small>";
  $("q-acertos").textContent = acertos; $("q-total").textContent = total;
}
$("q-btn").onclick = responder; $("q-prox").onclick = novaPergunta;
$("q-resp").onkeydown = function (e) { if (e.key === "Enter") { pergunta && pergunta.respondida ? novaPergunta() : responder(); } };
novaPergunta();
