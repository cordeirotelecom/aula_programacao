// Elaborado pelo Prof. Vagner Cordeiro
// TESTE AUTOMATICO de ponta a ponta: sobe broker, API, ingestor e simulador (com banco temporario),
// confere se os dados chegam ao banco e se o comando do app chega ao dispositivo.
const { spawn } = require("node:child_process");
const os = require("node:os");
const path = require("node:path");

const bancoTemp = path.join(os.tmpdir(), `teste_${Date.now()}.db`);
const env = { ...process.env, ARQUIVO_DB: bancoTemp, INTERVALO_MS: "300" };
const filhos = [];
const espera = (ms) => new Promise((r) => setTimeout(r, ms));

function iniciar(args) {
  const f = spawn(process.execPath, args, { cwd: __dirname, env, stdio: "ignore" });
  filhos.push(f);
}
function conferir(condicao, texto) {
  console.log((condicao ? "OK    " : "FALHOU") + " - " + texto);
  if (!condicao) { process.exitCode = 1; }
}
async function pegar(url, opcoes) { const r = await fetch(url, opcoes); return r.json(); }

(async () => {
  try {
    iniciar(["broker.js"]); await espera(1500);
    iniciar(["--experimental-sqlite", "--no-warnings", "api.js"]); await espera(1500);
    iniciar(["ingestor.js"]); await espera(1000);
    iniciar(["simulador.js"]); await espera(3000);

    const dados = await pegar("http://127.0.0.1:3000/api/dados");
    conferir(Array.isArray(dados) && dados.length === 1 && dados[0].dispositivo === "sala1", "API devolve a ultima leitura de sala1");
    const hist = await pegar("http://127.0.0.1:3000/api/historico?limite=50");
    conferir(hist.length >= 3, `banco acumulou leituras (${hist.length})`);

    const r = await pegar("http://127.0.0.1:3000/api/comando", {
      method: "POST", headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ dispositivo: "sala1", led: true }) });
    conferir(r.ok === true, "API aceitou o comando");
    await espera(1500);
    const depois = await pegar("http://127.0.0.1:3000/api/dados");
    conferir(depois[0].led === 1, "dispositivo obedeceu: LED aparece ligado na proxima leitura");

    const ruim = await fetch("http://127.0.0.1:3000/api/leituras", {
      method: "POST", headers: { "Content-Type": "application/json" }, body: JSON.stringify({ dispositivo: "../x" }) });
    conferir(ruim.status === 400, "API rejeita dados invalidos (400)");
    const trav = await fetch("http://127.0.0.1:3000/..%2f..%2fpackage.json");
    conferir(trav.status !== 200, "API nao serve arquivos fora de app/");
    const app = await fetch("http://127.0.0.1:3000/");
    conferir(app.status === 200, "app abre em /");
  } catch (e) {
    conferir(false, "erro inesperado: " + e.message);
  } finally {
    filhos.forEach((f) => f.kill());
    await espera(300);
    console.log(process.exitCode ? "\nTESTE COM FALHAS" : "\nTUDO CERTO - a integracao funciona.");
    process.exit(process.exitCode || 0);
  }
})();
// Executar (PowerShell): cd ".\integracao\02_projeto"; npm run teste
