const paginas = ["inicio", "programar", "teoria", "aulas", "redes", "iot", "hardware", "plataformas", "referencias", "guia"];
const programasPorId = new Map();
const materiaisPorId = new Map();
let programas = [];
let materiais = [];
let grupoPrograma = "todos";
let grupoAula = "todos";
let grupoRedes = "todos";
let grupoHardware = "todos";
let programaAtualId = null;
let materialHardwareAtual = null;
let saidaAnterior = "";
let erroVhdl = false;

const el = (id) => document.getElementById(id);

function grupoProgramaDe(programa) {
  const raiz = programa.id.split("/")[0];
  if (raiz === "cpp") return "C++";
  if (raiz === "c") return "C";
  return "C";
}

function grupoAulaDe(material) {
  const nomes = {
    web: "Web",
    redes: "Redes",
    ux_design: "UX/Design",
    mobile_iot: "Mobile IoT",
    esp32: "ESP32",
    sistemas_embarcados: "Sistemas embarcados",
    integracao: "Integração",
    "LEIA-ME": "Guias",
  };
  return nomes[material.grupo] || material.grupo;
}

function exibirPagina(nome) {
  if (!paginas.includes(nome)) return;
  for (const pagina of paginas) el(`pagina-${pagina}`).hidden = pagina !== nome;
  for (const botao of document.querySelectorAll(".aba")) {
    const ativa = botao.dataset.pagina === nome;
    botao.classList.toggle("ativa", ativa);
    botao.setAttribute("aria-current", ativa ? "page" : "false");
  }
  window.scrollTo({ top: 0, behavior: "smooth" });
  if (nome === "iot") atualizarIot();
}

for (const botao of document.querySelectorAll("[data-pagina]")) {
  botao.addEventListener("click", () => exibirPagina(botao.dataset.pagina));
}
for (const botao of document.querySelectorAll("[data-ir]")) {
  botao.addEventListener("click", () => exibirPagina(botao.dataset.ir));
}

async function requisicao(url, opcoes) {
  const resposta = await fetch(url, opcoes);
  const dados = await resposta.json();
  if (!resposta.ok) throw new Error(dados.erro || `Erro ${resposta.status}`);
  return dados;
}

function preencherFiltros(conteiner, grupos, valorAtual, escolher) {
  conteiner.replaceChildren();
  for (const grupo of ["todos", ...grupos]) {
    const botao = document.createElement("button");
    botao.type = "button";
    botao.className = `filtro${valorAtual === grupo ? " ativo" : ""}`;
    botao.textContent = grupo === "todos" ? "Todos" : grupo;
    botao.addEventListener("click", () => escolher(grupo));
    conteiner.append(botao);
  }
}

function adicionarVazio(conteiner, texto) {
  conteiner.replaceChildren();
  const mensagem = document.createElement("p");
  mensagem.className = "vazio";
  mensagem.textContent = texto;
  conteiner.append(mensagem);
}

function renderizarProgramas() {
  const termo = el("busca-programa").value.trim().toLocaleLowerCase("pt-BR");
  const filtrados = programas.filter((programa) =>
    (grupoPrograma === "todos" || grupoProgramaDe(programa) === grupoPrograma)
    && `${programa.nome} ${programa.id}`.toLocaleLowerCase("pt-BR").includes(termo));
  el("contagem").textContent = `${filtrados.length} de ${programas.length} programas`;
  const lista = el("lista-programas");
  lista.replaceChildren();
  if (!filtrados.length) return adicionarVazio(lista, "Nenhum programa encontrado.");

  for (const programa of filtrados) {
    const cartao = document.createElement("article");
    cartao.className = "programa";
    const info = document.createElement("div");
    info.className = "programa-info";
    const nome = document.createElement("span");
    nome.className = "programa-nome";
    nome.textContent = programa.nome;
    const caminho = document.createElement("span");
    caminho.className = "programa-pasta";
    caminho.textContent = programa.id;
    info.append(nome, caminho);
    const botao = document.createElement("button");
    botao.className = "executar";
    botao.type = "button";
    botao.textContent = "▶ Executar";
    botao.addEventListener("click", () => executarPrograma(programa.id));
    cartao.append(info, botao);
    lista.append(cartao);
  }
}

function materialEhAula(material) {
  return material.extensao === ".html";
}

function materialEhHardware(material) {
  return [".ino", ".vhd"].includes(material.extensao);
}

function renderizarBiblioteca(redes) {
  const sufixo = redes ? "redes" : "aula";
  const grupo = redes ? grupoRedes : grupoAula;
  const termo = el(`busca-${sufixo}`).value.trim().toLocaleLowerCase("pt-BR");
  const aulas = materiais.filter((material) =>
    materialEhAula(material) && (redes ? material.grupo === "redes" : material.grupo !== "redes"));
  const filtradas = aulas.filter((material) =>
    (grupo === "todos" || grupoAulaDe(material) === grupo)
    && `${material.nome} ${material.id} ${grupoAulaDe(material)}`.toLocaleLowerCase("pt-BR").includes(termo));
  el(`contagem-${redes ? "redes" : "aulas"}`).textContent = `${filtradas.length} de ${aulas.length} páginas`;
  const lista = el(`lista-${redes ? "redes" : "aulas"}`);
  const iframeId = redes ? "visualizador-redes" : "visualizador-aula";
  lista.replaceChildren();
  if (!filtradas.length) return adicionarVazio(lista, redes ? "Nenhum conteúdo de redes encontrado." : "Nenhuma aula encontrada.");

  for (const material of filtradas) {
    const botao = document.createElement("button");
    botao.type = "button";
    botao.className = "item-material";
    botao.classList.toggle("selecionado", el(iframeId).dataset.id === material.id);
    const nome = document.createElement("b");
    nome.textContent = material.nome.replace(/\.html$/i, "").replaceAll("_", " ");
    const caminho = document.createElement("small");
    caminho.textContent = material.id;
    botao.append(nome, caminho);
    botao.addEventListener("click", () => abrirAula(material, redes));
    lista.append(botao);
  }
}

function renderizarAulas() {
  renderizarBiblioteca(false);
}

function urlCurso(id) {
  return `/curso/${id.split("/").map(encodeURIComponent).join("/")}`;
}

function abrirAula(material, redes = false) {
  const sufixo = redes ? "redes" : "aula";
  const iframe = el(`visualizador-${sufixo}`);
  iframe.dataset.id = material.id;
  iframe.src = urlCurso(material.id);
  iframe.hidden = false;
  el(`placeholder-${sufixo}`).hidden = true;
  el(`titulo-${sufixo}`).textContent = material.nome.replace(/\.html$/i, "").replaceAll("_", " ");
  const link = el(`abrir-${sufixo}`);
  link.href = urlCurso(material.id);
  link.hidden = false;
  if (redes) renderizarBiblioteca(true);
  else renderizarAulas();
}

function renderizarHardware() {
  const termo = el("busca-hardware").value.trim().toLocaleLowerCase("pt-BR");
  const listaHardware = materiais.filter(materialEhHardware);
  const filtrados = listaHardware.filter((material) =>
    (grupoHardware === "todos" || material.grupo === grupoHardware)
    && `${material.nome} ${material.id}`.toLocaleLowerCase("pt-BR").includes(termo));
  el("contagem-hardware").textContent = `${filtrados.length} de ${listaHardware.length} códigos`;
  const lista = el("lista-hardware");
  lista.replaceChildren();
  if (!filtrados.length) return adicionarVazio(lista, "Nenhum exemplo encontrado.");

  for (const material of filtrados) {
    const botao = document.createElement("button");
    botao.type = "button";
    botao.className = "item-material";
    botao.classList.toggle("selecionado", materialHardwareAtual?.id === material.id);
    const nome = document.createElement("b");
    nome.textContent = material.nome.replace(/\.(ino|vhd)$/i, "").replaceAll("_", " ");
    const caminho = document.createElement("small");
    caminho.textContent = material.id;
    botao.append(nome, caminho);
    botao.addEventListener("click", () => abrirCodigoHardware(material));
    lista.append(botao);
  }
}

async function abrirCodigoHardware(material) {
  materialHardwareAtual = material;
  const codigo = el("codigo-hardware");
  el("placeholder-hardware").hidden = true;
  codigo.hidden = true;
  el("saida-vhdl").hidden = true;
  el("simular-vhdl").hidden = material.extensao !== ".vhd";
  el("copiar-codigo").hidden = false;
  el("simular-vhdl").disabled = false;
  el("simular-vhdl").textContent = "▶ Simular VHDL";
  el("titulo-hardware").textContent = material.nome;
  codigo.textContent = "Carregando código...";
  codigo.hidden = false;
  renderizarHardware();
  try {
    const resposta = await fetch(urlCurso(material.id));
    if (!resposta.ok) throw new Error(`Não foi possível carregar o arquivo (HTTP ${resposta.status}).`);
    codigo.textContent = await resposta.text();
  } catch (erro) {
    codigo.textContent = erro.message;
  }
}

function definirStatus(estado, programa) {
  const nomes = {
    parado: "Pronto para executar",
    compilando: `Compilando ${programa || "programa"}...`,
    executando: `Executando ${programa || "programa"}`,
    parando: "Encerrando programa...",
    concluido: "Programa concluído",
    erro: "O programa terminou com erro",
  };
  const ocupado = ["compilando", "executando", "parando"].includes(estado);
  el("status").replaceChildren();
  const ponto = document.createElement("span");
  ponto.className = `status-ponto${ocupado ? " ocupado" : estado === "concluido" ? " ok" : ""}`;
  el("status").append(ponto, document.createTextNode(` ${nomes[estado] || nomes.parado}`));
  el("parar").disabled = !ocupado;
  el("texto-entrada").disabled = estado !== "executando";
  el("enviar").disabled = estado !== "executando";
  el("ajuda-entrada").textContent = estado === "executando"
    ? "Digite o que o programa pedir e pressione Enter."
    : "A caixa é ativada enquanto um programa está rodando.";
  for (const botao of document.querySelectorAll(".executar")) botao.disabled = ocupado;
}

async function executarPrograma(id) {
  el("saida").textContent = "";
  el("texto-entrada").value = "";
  programaAtualId = null;
  try {
    const estado = await requisicao("/api/executar", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ id }),
    });
    programaAtualId = estado.id;
    saidaAnterior = "";
    const programa = programasPorId.get(id);
    definirStatus(estado.estado, programa?.nome);
    await buscarEstadoPrograma();
  } catch (erro) {
    el("saida").textContent = `Não foi possível iniciar: ${erro.message}`;
    definirStatus("erro");
  }
}

async function buscarEstadoPrograma() {
  try {
    const estado = await requisicao("/api/estado");
    if (estado.id && estado.id !== programaAtualId) {
      programaAtualId = estado.id;
      saidaAnterior = "";
    }
    if (estado.id !== programaAtualId) return;
    if (estado.saida !== saidaAnterior) {
      el("saida").textContent = estado.saida;
      saidaAnterior = estado.saida;
      el("saida").scrollTop = el("saida").scrollHeight;
    }
    definirStatus(estado.estado, programasPorId.get(estado.programa)?.nome);
  } catch (erro) {
    definirStatus("erro");
    el("saida").textContent = `Conexão com o laboratório perdida: ${erro.message}`;
  }
}

document.getElementById("form-entrada").addEventListener("submit", async (evento) => {
  evento.preventDefault();
  if (el("texto-entrada").disabled) return;
  try {
    await requisicao("/api/entrada", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ texto: el("texto-entrada").value }),
    });
    el("texto-entrada").value = "";
    el("texto-entrada").focus();
  } catch (erro) {
    el("ajuda-entrada").textContent = erro.message;
  }
});

el("parar").addEventListener("click", async () => {
  el("parar").disabled = true;
  try {
    await requisicao("/api/parar", { method: "POST", headers: { "Content-Type": "application/json" }, body: "{}" });
  } catch (erro) {
    el("ajuda-entrada").textContent = erro.message;
  }
});

function atualizarListaDeAulas() {
  const grupos = [...new Set(materiais.filter((material) => materialEhAula(material) && material.grupo !== "redes").map(grupoAulaDe))].sort((a, b) => a.localeCompare(b, "pt-BR"));
  preencherFiltros(el("filtros-aulas"), grupos, grupoAula, (valor) => {
    grupoAula = valor;
    atualizarListaDeAulas();
    renderizarAulas();
  });
  renderizarAulas();
}

function atualizarListaDeRedes() {
  const grupos = [...new Set(materiais.filter((material) => materialEhAula(material) && material.grupo === "redes").map(grupoAulaDe))].sort((a, b) => a.localeCompare(b, "pt-BR"));
  preencherFiltros(el("filtros-redes"), grupos, grupoRedes, (valor) => {
    grupoRedes = valor;
    atualizarListaDeRedes();
  });
  renderizarBiblioteca(true);
}

function atualizarListaDeHardware() {
  const grupos = [...new Set(materiais.filter(materialEhHardware).map((material) => material.grupo))].sort();
  preencherFiltros(el("filtros-hardware"), grupos, grupoHardware, (valor) => {
    grupoHardware = valor;
    atualizarListaDeHardware();
    renderizarHardware();
  });
  renderizarHardware();
}

function atualizarListaDeProgramas() {
  preencherFiltros(el("filtros-programas"), ["C", "C++"], grupoPrograma, (valor) => {
    grupoPrograma = valor;
    atualizarListaDeProgramas();
    renderizarProgramas();
  });
  renderizarProgramas();
}

el("busca-programa").addEventListener("input", renderizarProgramas);
el("busca-aula").addEventListener("input", renderizarAulas);
el("busca-redes").addEventListener("input", () => renderizarBiblioteca(true));
el("busca-hardware").addEventListener("input", renderizarHardware);

el("iniciar-iot").addEventListener("click", async () => {
  el("iniciar-iot").disabled = true;
  el("iniciar-iot").textContent = "Iniciando serviços...";
  try {
    await requisicao("/api/iot/iniciar", { method: "POST", headers: { "Content-Type": "application/json" }, body: "{}" });
    await atualizarIot();
  } catch (erro) {
    renderizarServicos([]);
    const aviso = document.createElement("p");
    aviso.className = "erro-iot";
    aviso.textContent = erro.message;
    el("status-iot").append(aviso);
    const servicos = erro.servicos;
    if (Array.isArray(servicos)) renderizarServicos(servicos);
  } finally {
    el("iniciar-iot").disabled = false;
    el("iniciar-iot").textContent = "▶ Iniciar simulação";
    await atualizarIot();
  }
});

el("parar-iot").addEventListener("click", async () => {
  el("parar-iot").disabled = true;
  try {
    await requisicao("/api/iot/parar", { method: "POST", headers: { "Content-Type": "application/json" }, body: "{}" });
    await atualizarIot();
  } catch (erro) {
    renderizarServicos([]);
    const aviso = document.createElement("p");
    aviso.className = "erro-iot";
    aviso.textContent = erro.message;
    el("status-iot").append(aviso);
  }
});

function renderizarServicos(servicos) {
  const container = el("status-iot");
  container.replaceChildren();
  if (!servicos.length) {
    const vazio = document.createElement("p");
    vazio.className = "placeholder";
    vazio.textContent = "Serviços ainda não iniciados.";
    container.append(vazio);
  } else {
    for (const servico of servicos) {
      const cartao = document.createElement("article");
      cartao.className = "cartao-servico";
      const estado = document.createElement("span");
      estado.className = `servico-ponto ${servico.estado}`;
      const nome = document.createElement("b");
      nome.textContent = servico.nome;
      const status = document.createElement("small");
      status.textContent = servico.estado;
      cartao.append(estado, nome, status);
      if (servico.saida) {
        const detalhe = document.createElement("pre");
        detalhe.textContent = servico.saida.trim().split("\n").slice(-4).join("\n");
        cartao.append(detalhe);
      }
      container.append(cartao);
    }
  }
  const rodando = servicos.some((servico) => ["iniciando", "rodando"].includes(servico.estado));
  el("iniciar-iot").disabled = rodando;
  el("iniciar-iot").textContent = rodando ? "Simulação ativa" : "▶ Iniciar simulação";
  el("parar-iot").disabled = !rodando;
  el("painel-iot").hidden = !rodando;
  if (rodando && el("iframe-iot").src === "about:blank") el("iframe-iot").src = "http://127.0.0.1:3000/";
}

async function atualizarIot() {
  try {
    renderizarServicos(await requisicao("/api/iot"));
  } catch (erro) {
    renderizarServicos([]);
    const aviso = document.createElement("p");
    aviso.className = "erro-iot";
    aviso.textContent = `Não foi possível consultar os serviços: ${erro.message}`;
    el("status-iot").append(aviso);
  }
}

el("simular-vhdl").addEventListener("click", async () => {
  if (!materialHardwareAtual || materialHardwareAtual.extensao !== ".vhd") return;
  const botao = el("simular-vhdl");
  const resultado = el("saida-vhdl");
  botao.disabled = true;
  botao.textContent = "Simulando...";
  resultado.hidden = false;
  resultado.textContent = "Analisando o arquivo VHDL e executando a simulação...";
  try {
    const resposta = await requisicao("/api/simular-vhdl", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ id: materialHardwareAtual.id }),
    });
    resultado.textContent = resposta.saida;
    erroVhdl = false;
  } catch (erro) {
    resultado.textContent = `A simulação não foi concluída.\n${erro.message}`;
    erroVhdl = true;
  } finally {
    botao.disabled = false;
    botao.textContent = erroVhdl ? "↻ Tentar novamente" : "▶ Simular VHDL";
  }
});

el("copiar-codigo").addEventListener("click", async () => {
  try {
    await navigator.clipboard.writeText(el("codigo-hardware").textContent);
    el("copiar-codigo").textContent = "Copiado!";
    setTimeout(() => { el("copiar-codigo").textContent = "Copiar código"; }, 1500);
  } catch {
    el("copiar-codigo").textContent = "Selecione e copie";
  }
});

async function carregarCatalogo() {
  try {
    [programas, materiais] = await Promise.all([
      requisicao("/api/programas"),
      requisicao("/api/materiais"),
    ]);
    for (const programa of programas) programasPorId.set(programa.id, programa);
    for (const material of materiais) materiaisPorId.set(material.id, material);
    el("total-programas").textContent = programas.length;
    el("total-aulas").textContent = materiais.filter(materialEhAula).length;
    atualizarListaDeProgramas();
    atualizarListaDeAulas();
    atualizarListaDeRedes();
    atualizarListaDeHardware();
    await buscarEstadoPrograma();
    await atualizarIot();
  } catch (erro) {
    el("total-programas").textContent = "!";
    el("total-aulas").textContent = "!";
    adicionarVazio(el("lista-programas"), `Não foi possível carregar programas: ${erro.message}`);
    adicionarVazio(el("lista-aulas"), `Não foi possível carregar as aulas: ${erro.message}`);
    adicionarVazio(el("lista-hardware"), `Não foi possível carregar os exemplos: ${erro.message}`);
  }
}

carregarCatalogo();
setInterval(buscarEstadoPrograma, 400);
setInterval(atualizarIot, 2000);
