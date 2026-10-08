// Elaborado pelo Prof. Vagner Cordeiro
// Funcoes puras de calculo de rede (sem DOM), testaveis no Node.

function ipParaNumero(texto) {
  const partes = texto.trim().split(".");
  if (partes.length !== 4) return null;
  let n = 0;
  for (const p of partes) {
    if (!/^\d{1,3}$/.test(p) || Number(p) > 255) return null;
    n = n * 256 + Number(p);
  }
  return n;
}

function numeroParaIp(n) {
  return [(n >>> 24) & 255, (n >>> 16) & 255, (n >>> 8) & 255, n & 255].join(".");
}

// cidr 0 e tratado a parte: deslocar 32 bits em JS nao zera o valor
function mascaraDeCidr(cidr) {
  return cidr === 0 ? 0 : (0xFFFFFFFF << (32 - cidr)) >>> 0;
}

function paraBinario(n) {
  return n.toString(2).padStart(32, "0").match(/.{8}/g).join(".");
}

function classeDoIp(n) {
  const a = n >>> 24;
  if (a === 0) return "reservada";
  if (a < 127) return "A";
  if (a === 127) return "loopback";
  if (a < 192) return "B";
  if (a < 224) return "C";
  if (a < 240) return "D (multicast)";
  return "E (reservada)";
}

function ehPrivado(n) {
  const a = n >>> 24, b = (n >>> 16) & 255;
  return a === 10 || (a === 172 && b >= 16 && b <= 31) || (a === 192 && b === 168);
}

function calcular(ipTexto, cidr) {
  const ip = ipParaNumero(ipTexto);
  if (ip === null || !Number.isInteger(cidr) || cidr < 0 || cidr > 32) return null;
  const mascara = mascaraDeCidr(cidr);
  const rede = (ip & mascara) >>> 0;
  const broadcast = (rede | ~mascara) >>> 0;
  const total = 2 ** (32 - cidr);
  let hosts, primeiro, ultimo;
  if (cidr === 32) { hosts = 1; primeiro = rede; ultimo = rede; }
  else if (cidr === 31) { hosts = 2; primeiro = rede; ultimo = broadcast; }
  else { hosts = total - 2; primeiro = rede + 1; ultimo = broadcast - 1; }
  return {
    ip, mascara, rede, broadcast, hosts,
    primeiro, ultimo, total,
    classe: classeDoIp(ip),
    privado: ehPrivado(ip),
    wildcard: (~mascara) >>> 0,
  };
}

// Divide uma rede em 'quantidade' sub-redes iguais
function dividir(ipTexto, cidr, quantidade) {
  const ip = ipParaNumero(ipTexto);
  if (ip === null || cidr < 0 || cidr > 30 || !(quantidade >= 1)) return null;
  let bits = 0;
  while (2 ** bits < quantidade) bits++;
  const novoCidr = cidr + bits;
  if (novoCidr > 30 || bits > 10) return null;
  const base = (ip & mascaraDeCidr(cidr)) >>> 0;
  const tamanho = 2 ** (32 - novoCidr);
  const lista = [];
  for (let i = 0; i < 2 ** bits; i++) {
    const rede = base + i * tamanho;
    lista.push({ rede, broadcast: rede + tamanho - 1, primeiro: rede + 1, ultimo: rede + tamanho - 2 });
  }
  return { novoCidr, bits, hostsPorRede: tamanho - 2, lista };
}

if (typeof module !== "undefined") {
  module.exports = { ipParaNumero, numeroParaIp, mascaraDeCidr, paraBinario, calcular, dividir };
}

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\redes\abrir.ps1" calculadora_web
