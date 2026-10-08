// Elaborado pelo Prof. Vagner Cordeiro
// Gera, em texto, o passo a passo (no papel) do calculo de rede e broadcast.
// Metodo: achar o "octeto interessante" (onde a mascara termina) e usar o tamanho do bloco.

function explicar(ipTexto, cidr) {
  var p = ipTexto.trim().split(".");
  var ok = p.length === 4 && p.every(function (x) { return /^\d{1,3}$/.test(x) && Number(x) <= 255; });
  if (!ok || !Number.isInteger(cidr) || cidr < 0 || cidr > 32) return null;
  var ip = p.map(Number);

  var k = Math.floor(cidr / 8);   // quantos octetos inteiros (255) tem a mascara
  var r = cidr % 8;               // bits "sobrando" no octeto interessante
  var passos = [];

  passos.push("PASSO 1 - Separe rede e host\n" +
    "  /" + cidr + " significa: " + cidr + " bits de REDE e " + (32 - cidr) + " bits de HOST (32 - " + cidr + ").");

  if (k === 4) {
    passos.push("PASSO 2 - Mascara\n  /32 = 255.255.255.255. Todos os bits sao de rede: e um unico endereco.\n" +
      "RESULTADO: rede = broadcast = " + ip.join(".") + " (1 host)");
    return passos;
  }

  var mascara = [];
  for (var i = 0; i < 4; i++) mascara.push(i < k ? 255 : (i === k ? 256 - Math.pow(2, 8 - r) : 0));
  var bloco = Math.pow(2, 8 - r);

  passos.push("PASSO 2 - Descubra a mascara\n" +
    "  " + cidr + " bits = " + k + " octetos cheios (255) + " + r + " bit(s) no proximo octeto.\n" +
    "  Octeto parcial: soma dos " + r + " primeiros pesos (128, 64, 32...) = " + mascara[k] + "\n" +
    "  Mascara = " + mascara.join("."));

  passos.push("PASSO 3 - Tamanho do bloco\n" +
    "  O octeto interessante e o " + (k + 1) + "o (valor da mascara: " + mascara[k] + ").\n" +
    "  Bloco = 256 - " + mascara[k] + " = " + bloco + "\n" +
    "  As redes neste octeto comecam em multiplos de " + bloco + ": 0, " + bloco + ", " + (2 * bloco) + ", ...");

  var redeK = Math.floor(ip[k] / bloco) * bloco;
  var rede = [], bc = [];
  for (var j = 0; j < 4; j++) {
    rede.push(j < k ? ip[j] : (j === k ? redeK : 0));
    bc.push(j < k ? ip[j] : (j === k ? redeK + bloco - 1 : 255));
  }

  passos.push("PASSO 4 - Endereco da REDE\n" +
    "  Octetos antes do interessante: copie o IP.\n" +
    "  Octeto interessante (" + ip[k] + "): qual multiplo de " + bloco + " vem logo antes dele? " +
    Math.floor(ip[k] / bloco) + " x " + bloco + " = " + redeK + "\n" +
    "  Octetos depois: 0.\n" +
    "  REDE = " + rede.join(".") + "/" + cidr);

  passos.push("PASSO 5 - Endereco de BROADCAST\n" +
    "  Octeto interessante: " + redeK + " + " + bloco + " - 1 = " + (redeK + bloco - 1) + "\n" +
    "  Octetos depois: 255.\n" +
    "  BROADCAST = " + bc.join("."));

  var hosts = cidr >= 31 ? (cidr === 31 ? 2 : 1) : Math.pow(2, 32 - cidr) - 2;
  var ultimo = bc.slice(), primeiro = rede.slice();
  if (cidr < 31) { primeiro[3] += 1; ultimo[3] -= 1; }
  passos.push("PASSO 6 - Primeiro e ultimo host, quantidade\n" +
    (cidr < 31
      ? "  Primeiro host = rede + 1 = " + primeiro.join(".") + "\n  Ultimo host   = broadcast - 1 = " + ultimo.join(".") + "\n" +
        "  Hosts = 2^" + (32 - cidr) + " - 2 = " + hosts
      : "  /" + cidr + " e um caso especial (sem rede/broadcast tradicionais). Hosts: " + hosts));

  passos.push("PASSO 7 - Prova (opcional): E binario\n" +
    "  IP    = " + ip.map(function (n) { return n.toString(2).padStart(8, "0"); }).join(".") + "\n" +
    "  Masc. = " + mascara.map(function (n) { return n.toString(2).padStart(8, "0"); }).join(".") + "\n" +
    "  AND   = " + rede.map(function (n) { return n.toString(2).padStart(8, "0"); }).join(".") + "  <- deve igualar a REDE");

  return passos;
}

if (typeof module !== "undefined") { module.exports = { explicar: explicar }; }

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\redes\abrir.ps1" 10_passo_a_passo_calculo
