// Elaborado pelo Prof. Vagner Cordeiro
// Service worker: guarda os arquivos do app para abrir mesmo sem internet.
// Dados do dispositivo (/dados, /led) NUNCA vao para o cache: sempre ao vivo.

var NOME_CACHE = "painel-sensores-v1";
var ARQUIVOS = ["./", "index.html", "estilo.css", "script.js", "manifest.json", "icone.svg", "../logica.js"];

self.addEventListener("install", function (evento) {
  evento.waitUntil(caches.open(NOME_CACHE).then(function (cache) { return cache.addAll(ARQUIVOS); }));
  self.skipWaiting();
});

self.addEventListener("activate", function (evento) {
  evento.waitUntil(caches.keys().then(function (nomes) {
    return Promise.all(nomes.filter(function (n) { return n !== NOME_CACHE; }).map(function (n) { return caches.delete(n); }));
  }));
});

self.addEventListener("fetch", function (evento) {
  var url = new URL(evento.request.url);
  if (url.origin !== location.origin) return;   // pedidos ao ESP32 passam direto
  evento.respondWith(
    fetch(evento.request).catch(function () { return caches.match(evento.request); })
  );
});

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\mobile_iot\servidor.ps1"
