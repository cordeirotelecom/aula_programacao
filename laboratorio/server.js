// Servidor local do curso: serve materiais do proprio curso e executa exemplos C/C++.
const http = require("node:http");
const fs = require("node:fs");
const os = require("node:os");
const path = require("node:path");
const { spawn } = require("node:child_process");
const { execFile } = require("node:child_process");

const RAIZ = path.resolve(__dirname, "..");
const ENDERECO = "127.0.0.1";
const PORTA = Number(process.env.PORTA_LABORATORIO || 47831);
const ARQUIVOS_PUBLICOS = {
  "/": ["index.html", "text/html; charset=utf-8"],
  "/app.js": ["app.js", "text/javascript; charset=utf-8"],
  "/style.css": ["style.css", "text/css; charset=utf-8"],
  "/tema.css": ["tema.css", "text/css; charset=utf-8"],
  "/extras.js": ["extras.js", "text/javascript; charset=utf-8"],
};
const DOWNLOADS_RAIZ = new Set([
  "instalar_professor.ps1",
  "preparar_aluno.ps1",
  "executar.ps1",
  "README.md",
  "LEIA-ME.txt",
  "abrir_laboratorio.bat",
]);
const LIMITE_LOG = 64 * 1024;
let execucaoAtual = null;
let proximoId = 1;
let servicosIot = [];

const TIPOS_MIME = {
  ".html": "text/html; charset=utf-8",
  ".css": "text/css; charset=utf-8",
  ".js": "text/javascript; charset=utf-8",
  ".json": "application/json; charset=utf-8",
  ".svg": "image/svg+xml",
  ".png": "image/png",
  ".jpg": "image/jpeg",
  ".jpeg": "image/jpeg",
  ".gif": "image/gif",
  ".webp": "image/webp",
  ".ico": "image/x-icon",
  ".woff": "font/woff",
  ".woff2": "font/woff2",
  ".ttf": "font/ttf",
  ".ino": "text/plain; charset=utf-8",
  ".vhd": "text/plain; charset=utf-8",
  ".c": "text/plain; charset=utf-8",
  ".cpp": "text/plain; charset=utf-8",
};
const EXTENSOES_MATERIAL = new Set(Object.keys(TIPOS_MIME));

function listarArquivos(pasta, extensoes, arquivos = []) {
  for (const entrada of fs.readdirSync(pasta, { withFileTypes: true })) {
    if (entrada.name.startsWith(".")) continue;
    const caminho = path.join(pasta, entrada.name);
    if (entrada.isDirectory()) {
      if (entrada.name !== "node_modules" && entrada.name !== "laboratorio" && entrada.name !== ".git") {
        listarArquivos(caminho, extensoes, arquivos);
      }
    } else if (entrada.isFile() && extensoes.has(path.extname(entrada.name).toLowerCase())) {
      arquivos.push(caminho);
    }
  }
  return arquivos;
}

const arquivosCurso = listarArquivos(RAIZ, EXTENSOES_MATERIAL);
const idsMateriais = new Set(arquivosCurso.map((arquivo) => path.relative(RAIZ, arquivo).replace(/\\/g, "/")));
const programas = new Map([".c", ".cpp"].flatMap((ext) =>
  arquivosCurso
    .filter((arquivo) => path.extname(arquivo).toLowerCase() === ext)
    .sort((a, b) => a.localeCompare(b, "pt-BR"))
    .map((arquivo) => {
      const id = path.relative(RAIZ, arquivo).replace(/\\/g, "/");
      return [id, { id, arquivo, nome: path.basename(arquivo, ext), linguagem: ext === ".c" ? "c" : "cpp" }];
    }),
));

const materiais = arquivosCurso
  .filter((arquivo) => path.extname(arquivo).toLowerCase() !== ".c" && path.extname(arquivo).toLowerCase() !== ".cpp")
  .map((arquivo) => {
    const id = path.relative(RAIZ, arquivo).replace(/\\/g, "/");
    return { id, nome: path.basename(arquivo), grupo: id.split("/")[0], extensao: path.extname(arquivo).toLowerCase() };
  })
  .sort((a, b) => a.id.localeCompare(b.id, "pt-BR"));

const arquivosExecutaveis = new Map();
for (const [id, programa] of programas) {
  arquivosExecutaveis.set(path.resolve(programa.arquivo), id);
}

function adicionarSaida(execucao, texto) {
  execucao.saida += texto;
  if (execucao.saida.length > LIMITE_LOG) {
    execucao.saida = `[Saída antiga removida para limitar o histórico.]\n${execucao.saida.slice(-LIMITE_LOG)}`;
  }
}

function responder(res, status, dados) {
  res.writeHead(status, {
    "Content-Type": "application/json; charset=utf-8",
    "Cache-Control": "no-store",
    "X-Content-Type-Options": "nosniff",
  });
  res.end(JSON.stringify(dados));
}

function origemLocal(req) {
  const origem = req.headers.origin;
  if (!origem) return true;
  try {
    return new URL(origem).origin === `http://${ENDERECO}:${PORTA}`;
  } catch {
    return false;
  }
}

function lerJson(req) {
  return new Promise((resolve, reject) => {
    let corpo = "";
    req.on("data", (parte) => {
      corpo += parte;
      if (corpo.length > 4096) {
        reject(new Error("Requisição muito grande."));
        req.destroy();
      }
    });
    req.on("end", () => {
      try {
        resolve(JSON.parse(corpo || "{}"));
      } catch {
        reject(new Error("JSON inválido."));
      }
    });
    req.on("error", reject);
  });
}

function estadoAtual() {
  if (!execucaoAtual) return { estado: "parado", saida: "" };
  return {
    id: execucaoAtual.id,
    programa: execucaoAtual.programa,
    linguagem: execucaoAtual.linguagem,
    estado: execucaoAtual.estado,
    saida: execucaoAtual.saida,
    codigoSaida: execucaoAtual.codigoSaida,
  };
}

function iniciarPrograma(programa) {
  const id = proximoId++;
  const exe = path.join(path.dirname(programa.arquivo), `${programa.nome}.exe`);
  const execucao = {
    id,
    programa: programa.id,
    linguagem: programa.linguagem,
    estado: "compilando",
    saida: `$ ${programa.linguagem === "c" ? "gcc -std=c11" : "g++ -std=c++17"} -Wall -Wextra "${programa.nome}${programa.linguagem === "c" ? ".c" : ".cpp"}" -o "${programa.nome}.exe"\n`,
    codigoSaida: null,
    processo: null,
    pararSolicitado: false,
  };
  execucaoAtual = execucao;

  const comando = programa.linguagem === "c" ? "gcc" : "g++";
  const padrao = programa.linguagem === "c" ? "-std=c11" : "-std=c++17";
  const compilador = spawn(comando, [padrao, "-Wall", "-Wextra", "-include", path.join(__dirname, "flush_stdout.h"), programa.arquivo, "-o", exe], {
    cwd: path.dirname(programa.arquivo),
    windowsHide: true,
  });
  execucao.processo = compilador;
  compilador.stdout.setEncoding("utf8").on("data", (texto) => adicionarSaida(execucao, texto));
  compilador.stderr.setEncoding("utf8").on("data", (texto) => adicionarSaida(execucao, texto));
  compilador.on("error", (erro) => {
    adicionarSaida(execucao, `\nErro ao iniciar o GCC: ${erro.message}\n`);
    execucao.estado = "erro";
    execucao.codigoSaida = 1;
  });
  compilador.on("close", (codigo) => {
    if (execucao.pararSolicitado) {
      execucao.estado = "parado";
      execucao.codigoSaida = codigo;
      return;
    }
    if (codigo !== 0) {
      execucao.estado = "erro";
      execucao.codigoSaida = codigo;
      adicionarSaida(execucao, `\nCompilação encerrada com código ${codigo}.\n`);
      return;
    }

    adicionarSaida(execucao, `\n$ .\\${programa.nome}.exe\n`);
    execucao.estado = "executando";
    const filho = spawn(exe, [], { cwd: path.dirname(programa.arquivo), windowsHide: true });
    execucao.processo = filho;
    filho.stdout.setEncoding("utf8").on("data", (texto) => adicionarSaida(execucao, texto));
    filho.stderr.setEncoding("utf8").on("data", (texto) => adicionarSaida(execucao, texto));
    filho.on("error", (erro) => {
      adicionarSaida(execucao, `\nErro ao iniciar o programa: ${erro.message}\n`);
      execucao.estado = "erro";
      execucao.codigoSaida = 1;
    });
    filho.on("close", (codigoFilho) => {
      execucao.codigoSaida = codigoFilho;
      execucao.estado = execucao.pararSolicitado ? "parado" : codigoFilho === 0 ? "concluido" : "erro";
      if (!execucao.pararSolicitado) adicionarSaida(execucao, `\n[Programa encerrado: código ${codigoFilho}]\n`);
    });
  });
}

function servirMaterial(req, res, pathname) {
  let id;
  try {
    id = decodeURIComponent(pathname.slice("/curso/".length));
  } catch {
    return responder(res, 400, { erro: "Caminho inválido." });
  }
  if (!id || id.includes("\0") || id.includes("\\")) return responder(res, 400, { erro: "Arquivo inválido." });
  const arquivo = path.resolve(RAIZ, id);
  const relativo = path.relative(RAIZ, arquivo);
  if (!relativo || relativo === ".." || relativo.startsWith(`..${path.sep}`) || path.isAbsolute(relativo)) {
    return responder(res, 403, { erro: "Acesso negado." });
  }
  const extensao = path.extname(arquivo).toLowerCase();
  if (!idsMateriais.has(id.replace(/\\/g, "/")) || !EXTENSOES_MATERIAL.has(extensao)
    || !fs.existsSync(arquivo) || !fs.statSync(arquivo).isFile()) {
    return responder(res, 404, { erro: "Material não encontrado." });
  }
  fs.readFile(arquivo, (erro, conteudo) => {
    if (erro) return responder(res, 404, { erro: "Não foi possível ler o material." });
    res.writeHead(200, {
      "Content-Type": TIPOS_MIME[extensao],
      "X-Content-Type-Options": "nosniff",
      "X-Frame-Options": "SAMEORIGIN",
      "Cache-Control": "no-store",
    });
    res.end(conteudo);
  });
}

function estadoIot() {
  return servicosIot.map(({ nome, processo, estado, saida }) => ({
    nome,
    estado: processo && (processo.exitCode !== null || processo.signalCode !== null)
      ? estado === "erro" ? "erro" : "parado"
      : estado,
    saida,
  }));
}

function iniciarServico(nome, arquivo, args, ambiente = {}) {
  const proc = spawn(process.execPath, args, {
    cwd: path.dirname(arquivo),
    env: { ...process.env, ...ambiente },
    windowsHide: true,
  });
  const servico = { nome, processo: proc, estado: "iniciando", saida: "" };
  servicosIot.push(servico);
  proc.stdout.setEncoding("utf8").on("data", (texto) => {
    servico.saida = `${servico.saida}${texto}`.slice(-8000);
  });
  proc.stderr.setEncoding("utf8").on("data", (texto) => {
    servico.saida = `${servico.saida}${texto}`.slice(-8000);
  });
  proc.once("spawn", () => { servico.estado = "rodando"; });
  proc.once("error", (erro) => {
    servico.estado = "erro";
    servico.saida += `\nFalha ao iniciar: ${erro.message}`;
  });
  proc.once("exit", (codigo, sinal) => {
    if (servico.estado === "parando") {
      servico.estado = "parado";
      return;
    }
    servico.estado = codigo === 0 ? "parado" : "erro";
    if (servico.estado === "erro") {
      const motivo = sinal ? `sinal ${sinal}` : `código ${codigo}`;
      servico.saida += `\nProcesso terminou com ${motivo}.`;
    }
  });
  return servico;
}

async function aguardar(condicao, descricao, timeout = 10000) {
  const inicio = Date.now();
  while (Date.now() - inicio < timeout) {
    if (condicao()) return;
    await new Promise((resolve) => setTimeout(resolve, 200));
  }
  throw new Error(`Tempo esgotado aguardando ${descricao}. Confira as portas 1883 e 3000.`);
}

async function iniciarIot() {
  if (servicosIot.some((servico) => servico.processo.exitCode === null)) {
    throw new Error("A integração já está iniciada. Pare os serviços antes de iniciar novamente.");
  }
  const pasta = path.join(RAIZ, "integracao", "02_projeto");
  for (const dependencia of ["aedes", "mqtt"]) {
    try {
      require.resolve(dependencia, { paths: [pasta] });
    } catch {
      throw new Error("Dependências IoT ausentes. Na pasta integracao\\02_projeto, execute npm install e tente novamente.");
    }
  }
  servicosIot = [];
  const broker = iniciarServico("Broker MQTT", path.join(pasta, "broker.js"), [path.join(pasta, "broker.js")], { MQTT_HOST: "127.0.0.1" });
  await aguardar(() => broker.estado === "rodando" && /ouvindo/.test(broker.saida), "Broker MQTT");
  const api = iniciarServico("API + aplicativo", path.join(pasta, "api.js"), [
    "--experimental-sqlite", "--no-warnings", path.join(pasta, "api.js"),
  ], { HOST_API: "127.0.0.1" });
  await aguardar(() => api.estado === "erro" || /pronta em/.test(api.saida), "API");
  if (api.estado === "erro") throw new Error(api.saida);
  iniciarServico("Ingestor MQTT", path.join(pasta, "ingestor.js"), [path.join(pasta, "ingestor.js")], { MQTT_URL: "mqtt://127.0.0.1:1883" });
  iniciarServico("Simulador de sensores", path.join(pasta, "simulador.js"), [path.join(pasta, "simulador.js")], {
    MQTT_URL: "mqtt://127.0.0.1:1883",
    INTERVALO_MS: "1500",
  });
  return estadoIot();
}

async function pararIot() {
  const encerrando = [];
  for (const servico of servicosIot) {
    if (servico.processo.exitCode === null && servico.processo.signalCode === null) {
      servico.estado = "parando";
      encerrando.push(new Promise((resolve) => {
        servico.processo.once("exit", resolve);
        setTimeout(resolve, 2500).unref();
      }));
      servico.processo.kill();
    }
  }
  await Promise.all(encerrando);
  return estadoIot();
}

function caminhoGhdl() {
  const bin = path.join(process.env.LOCALAPPDATA || "", "ghdl", "bin", "ghdl.exe");
  if (fs.existsSync(bin)) return bin;
  return "ghdl";
}

async function simularVhdl(id) {
  const material = materiais.find((item) => item.id === id && item.extensao === ".vhd");
  if (!material) throw new Error("Exemplo VHDL não encontrado.");
  const temporario = fs.mkdtempSync(path.join(os.tmpdir(), "laboratorio-vhdl-"));
  const chamar = (args) => new Promise((resolve, reject) => {
    const proc = spawn(caminhoGhdl(), args, { cwd: temporario, windowsHide: true });
    let saida = "";
    proc.stdout.setEncoding("utf8").on("data", (texto) => { saida += texto; });
    proc.stderr.setEncoding("utf8").on("data", (texto) => { saida += texto; });
    proc.once("error", (erro) => reject(new Error(`GHDL indisponível: ${erro.message}. Instale pelo roteiro VHDL do curso.`)));
    proc.once("close", (codigo) => codigo === 0 ? resolve(saida) : reject(new Error(saida || `GHDL terminou com código ${codigo}.`)));
  });
  try {
    const fonte = path.resolve(RAIZ, id);
    let saida = `$ ghdl -a --std=08 "${material.nome}"\n`;
    saida += await chamar(["-a", "--std=08", `--workdir=${temporario}`, fonte]);
    saida += `\n$ ghdl -e --std=08 tb\n`;
    saida += await chamar(["-e", "--std=08", `--workdir=${temporario}`, "tb"]);
    saida += `\n$ ghdl -r --std=08 tb --stop-time=100ms\n`;
    saida += await chamar(["-r", "--std=08", `--workdir=${temporario}`, "tb", "--stop-time=100ms"]);
    return saida || "Simulação concluída sem mensagens.";
  } finally {
    fs.rmSync(temporario, { recursive: true, force: true });
  }
}

const servidor = http.createServer(async (req, res) => {
  const url = new URL(req.url, `http://${ENDERECO}:${PORTA}`);

  if (req.method === "GET" && url.pathname === "/api/programas") {
    return responder(res, 200, Array.from(programas.values(), ({ id, nome, linguagem }) => ({ id, nome, linguagem })));
  }
  if (req.method === "GET" && url.pathname === "/api/materiais") {
    return responder(res, 200, materiais);
  }
  if (req.method === "GET" && url.pathname === "/api/iot") {
    return responder(res, 200, estadoIot());
  }
  if (req.method === "GET" && url.pathname === "/api/estado") {
    return responder(res, 200, estadoAtual());
  }

  if (req.method === "POST") {
    if (!origemLocal(req)) return responder(res, 403, { erro: "Origem não permitida." });
    let dados;
    try {
      dados = await lerJson(req);
    } catch (erro) {
      return responder(res, 400, { erro: erro.message });
    }

    if (url.pathname === "/api/executar") {
      const programa = typeof dados.id === "string" ? programas.get(dados.id) : null;
      if (!programa) return responder(res, 404, { erro: "Programa não encontrado." });
      if (execucaoAtual && ["compilando", "executando"].includes(execucaoAtual.estado)) {
        return responder(res, 409, { erro: "Pare o programa atual antes de iniciar outro." });
      }
      iniciarPrograma(programa);
      return responder(res, 202, estadoAtual());
    }
    if (url.pathname === "/api/simular-vhdl") {
      try {
        const saida = await simularVhdl(dados.id);
        return responder(res, 200, { saida });
      } catch (erro) {
        return responder(res, 422, { erro: erro.message });
      }
    }
    if (url.pathname === "/api/iot/iniciar") {
      try {
        return responder(res, 202, await iniciarIot());
      } catch (erro) {
        return responder(res, 409, { erro: erro.message, servicos: estadoIot() });
      }
    }
    if (url.pathname === "/api/iot/parar") {
      return responder(res, 200, await pararIot());
    }
    if (url.pathname === "/api/entrada") {
      if (!execucaoAtual || execucaoAtual.estado !== "executando" || !execucaoAtual.processo?.stdin?.writable) {
        return responder(res, 409, { erro: "Nenhum programa está aguardando entrada." });
      }
      if (typeof dados.texto !== "string" || dados.texto.length > 1000) {
        return responder(res, 400, { erro: "Digite até 1000 caracteres." });
      }
      execucaoAtual.processo.stdin.write(`${dados.texto}\n`);
      return responder(res, 202, { ok: true });
    }
    if (url.pathname === "/api/parar") {
      if (!execucaoAtual || !["compilando", "executando"].includes(execucaoAtual.estado)) {
        return responder(res, 409, { erro: "Não há programa em execução." });
      }
      execucaoAtual.pararSolicitado = true;
      execucaoAtual.estado = "parando";
      execucaoAtual.processo?.kill();
      return responder(res, 202, { ok: true });
    }
  }

  if (req.method === "GET") {
    if (url.pathname.startsWith("/curso/")) return servirMaterial(req, res, url.pathname);
    if (url.pathname.startsWith("/baixar/")) {
      let nome;
      try {
        nome = decodeURIComponent(url.pathname.slice("/baixar/".length));
      } catch {
        return responder(res, 400, { erro: "Caminho inválido." });
      }
      if (!DOWNLOADS_RAIZ.has(nome)) return responder(res, 404, { erro: "Arquivo não disponível para download." });
      return fs.readFile(path.join(RAIZ, nome), (erro, conteudo) => {
        if (erro) return responder(res, 404, { erro: "Não foi possível ler o arquivo." });
        res.writeHead(200, {
          "Content-Type": "application/octet-stream",
          "Content-Disposition": `attachment; filename="${nome}"`,
          "X-Content-Type-Options": "nosniff",
          "Cache-Control": "no-store",
        });
        res.end(conteudo);
      });
    }
    const arquivo = ARQUIVOS_PUBLICOS[url.pathname];
    if (arquivo) {
      fs.readFile(path.join(__dirname, arquivo[0]), (erro, conteudo) => {
        if (erro) return responder(res, 500, { erro: "Não foi possível abrir a interface." });
        res.writeHead(200, {
          "Content-Type": arquivo[1],
          "X-Content-Type-Options": "nosniff",
          "Content-Security-Policy": "default-src 'self'; style-src 'self' 'unsafe-inline'; script-src 'self'; connect-src 'self'; frame-src 'self' http://127.0.0.1:3000 https://*.manus.space",
        });
        res.end(conteudo);
      });
      return;
    }
  }

  responder(res, 404, { erro: "Não encontrado." });
});

servidor.on("error", (erro) => {
  console.error(`Não foi possível iniciar o laboratório: ${erro.message}`);
  process.exitCode = 1;
});
function encerrarServidor() {
  void pararIot();
  if (execucaoAtual?.processo && execucaoAtual.processo.exitCode === null) execucaoAtual.processo.kill();
  servidor.close(() => process.exit());
  setTimeout(() => process.exit(1), 3000).unref();
}
process.on("SIGINT", encerrarServidor);
process.on("SIGTERM", encerrarServidor);
servidor.listen(PORTA, ENDERECO, () => {
  const url = `http://${ENDERECO}:${PORTA}`;
  console.log(`Laboratório pronto: ${url}`);
  console.log(`${programas.size} programas C/C++ e ${materiais.length} materiais encontrados. Pressione Ctrl+C para encerrar.`);
  if (process.env.ABRIR_NAVEGADOR !== "0") {
    execFile("cmd.exe", ["/c", "start", "", url], (erro) => {
      if (erro) console.log(`Abra este endereço no navegador: ${url}`);
    });
  }
});
