(() => {
  const $ = (id) => document.getElementById(id);

  const PLATAFORMAS = [
    ["Programação", "Plataforma de Programação", "Conteúdo de programação do curso.", "https://interfaceedu-4y8rdsta.manus.space/programacao"],
    ["Programação", "Roteiro de Programação", "Roteiro de estudo passo a passo.", "https://interfaceedu-4y8rdsta.manus.space/roteiro-programacao"],
    ["Eletrônica e embarcados", "Sistemas Embarcados", "Microcontroladores e sistemas embarcados.", "https://interfaceedu-4y8rdsta.manus.space/sistemas-embarcados"],
    ["Eletrônica e embarcados", "Eletrônica", "Fundamentos de eletrônica.", "https://interfaceedu-4y8rdsta.manus.space/?code=GvKVCR6RbbKrFX4Z6fdCqu"],
    ["InstEduca", "InstEduca", "Plataforma educacional InstEduca.", "https://insteduca-tddzd5wq.manus.space/"],
    ["InstEduca", "Node-RED", "Automação visual com Node-RED.", "https://insteduca-tddzd5wq.manus.space/nodered"],
    ["POO e Pesquisa Operacional", "Programação Orientada a Objetos", "Conceitos de POO.", "https://vagneroop-533ejnqb.manus.space/"],
    ["POO e Pesquisa Operacional", "Pesquisa Operacional", "Modelagem e otimização.", "https://vagneroop-533ejnqb.manus.space/pesquisa-operacional"],
    ["Redes e IoT", "Redes IoT", "Redes aplicadas à Internet das Coisas.", "https://redesiot-26j55vwj.manus.space/?code=C2uxidBNspRfWuEsWiUwWB"],
  ];

  function criar(tag, atributos = {}, texto) {
    const no = document.createElement(tag);
    for (const [k, v] of Object.entries(atributos)) no.setAttribute(k, v);
    if (texto !== undefined) no.textContent = texto;
    return no;
  }

  function montarPlataformas() {
    const lista = $("lista-plataformas");
    if (!lista) return;
    let grupoAtual = "";
    for (const [grupo, titulo, descricao, url] of PLATAFORMAS) {
      if (grupo !== grupoAtual) {
        grupoAtual = grupo;
        lista.append(criar("h3", { class: "grupo-titulo" }, grupo));
      }
      const botao = criar("button", { type: "button", class: "item-material" });
      botao.append(criar("b", {}, titulo), criar("small", {}, descricao));
      botao.addEventListener("click", () => {
        for (const outro of lista.querySelectorAll(".item-material")) outro.classList.remove("ativo");
        botao.classList.add("ativo");
        $("titulo-plataformas").textContent = titulo;
        $("placeholder-plataformas").hidden = true;
        const frame = $("visualizador-plataformas");
        frame.hidden = false;
        frame.src = url;
        const abrir = $("abrir-plataformas");
        abrir.href = url;
        abrir.hidden = false;
      });
      lista.append(botao);
    }
  }

  function montarGerador() {
    const form = $("form-ref");
    if (!form) return;
    const v = (id) => $(id).value.trim();
    const maiusculo = (autor) => {
      const [sobrenome, ...resto] = autor.split(",");
      return resto.length ? `${sobrenome.trim().toUpperCase()}, ${resto.join(",").trim()}` : autor.toUpperCase();
    };
    const atualizar = () => {
      const tipo = v("ref-tipo");
      for (const rotulo of form.querySelectorAll("[data-so]")) {
        rotulo.hidden = !rotulo.dataset.so.split(",").includes(tipo);
      }
      const autor = v("ref-autor") ? maiusculo(v("ref-autor")) : "";
      const titulo = v("ref-titulo");
      const ano = v("ref-ano");
      const saida = $("ref-saida");
      saida.replaceChildren();
      if (!autor || !titulo) {
        saida.textContent = "Preencha ao menos autor e título.";
        return;
      }
      saida.append(`${autor}. `, criar("b", {}, titulo));
      if (tipo === "livro") {
        const partes = [v("ref-edicao"), [v("ref-local") || "[s. l.]", v("ref-editora") || "[s. n.]"].join(": ")];
        saida.append(`. ${partes.filter(Boolean).join(". ")}, ${ano || "[s. d.]"}.`);
      } else if (tipo === "artigo") {
        saida.append(`. ${v("ref-local") || "Periódico"}, ${ano || "[s. d.]"}.`);
      } else {
        const hoje = new Date().toLocaleDateString("pt-BR", { day: "numeric", month: "short", year: "numeric" });
        saida.append(`. ${ano ? ano + ". " : ""}Disponível em: ${v("ref-url") || "URL"}. Acesso em: ${hoje}.`);
      }
    };
    form.addEventListener("input", atualizar);
    form.addEventListener("change", atualizar);
    form.addEventListener("submit", (e) => e.preventDefault());
    $("ref-copiar").addEventListener("click", async (e) => {
      const botao = e.currentTarget;
      try {
        await navigator.clipboard.writeText($("ref-saida").textContent);
        botao.textContent = "Copiado!";
      } catch {
        botao.textContent = "Selecione e copie manualmente";
      }
      setTimeout(() => (botao.textContent = "Copiar referência"), 1800);
    });
    atualizar();
  }

  const PALAVRAS = new Set((
    "auto break case char const continue default do double else enum extern float for goto if inline int long register return short signed sizeof static struct switch typedef union unsigned void volatile while " +
    "class public private protected namespace using new delete template typename virtual bool true false nullptr this try catch throw include define " +
    "String byte boolean setup loop pinMode digitalWrite digitalRead analogRead analogWrite delay Serial HIGH LOW INPUT OUTPUT " +
    "library use entity architecture is of port map signal begin end process in out std_logic std_logic_vector if then elsif else when others component"
  ).split(" "));
  const TOKEN = /(\/\/[^\n]*|--[^\n]*|\/\*[\s\S]*?\*\/|#\s*\w+|"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])'|\b\d+(?:\.\d+)?\b|\b[A-Za-z_]\w*\b)/g;

  function colorir(pre) {
    if (pre.querySelector("span.tk") || !pre.textContent) return;
    const texto = pre.textContent;
    const fragmento = document.createDocumentFragment();
    let ultimo = 0;
    for (const m of texto.matchAll(TOKEN)) {
      const t = m[0];
      let classe = "";
      if (t.startsWith("//") || t.startsWith("--") || t.startsWith("/*")) classe = "tk-com";
      else if (t[0] === "#") classe = "tk-pre";
      else if (t[0] === '"' || t[0] === "'") classe = "tk-str";
      else if (/^\d/.test(t)) classe = "tk-num";
      else if (PALAVRAS.has(t) || PALAVRAS.has(t.toLowerCase())) classe = "tk-kw";
      else if (texto[m.index + t.length] === "(") classe = "tk-fn";
      if (!classe) continue;
      if (m.index > ultimo) fragmento.append(texto.slice(ultimo, m.index));
      fragmento.append(criar("span", { class: `tk ${classe}` }, t));
      ultimo = m.index + t.length;
    }
    fragmento.append(texto.slice(ultimo));
    pre.replaceChildren(fragmento);
  }

  function observarCodigo() {
    for (const pre of document.querySelectorAll(".conceito-conteudo pre")) colorir(pre);
    const hw = $("codigo-hardware");
    if (!hw) return;
    new MutationObserver(() => colorir(hw)).observe(hw, { childList: true, characterData: true });
  }

  function baixarCodigo() {
    const hw = $("codigo-hardware");
    const acoes = document.querySelector("#pagina-hardware .acoes-codigo");
    if (!hw || !acoes) return;
    const botao = criar("button", { type: "button", class: "botao-secundario", hidden: "" }, "⬇ Baixar código");
    botao.addEventListener("click", () => {
      const nome = ($("titulo-hardware").textContent.trim().replace(/[^\w.-]+/g, "_") || "codigo") + ".txt";
      const url = URL.createObjectURL(new Blob([hw.textContent], { type: "text/plain;charset=utf-8" }));
      const a = criar("a", { href: url, download: nome });
      document.body.append(a);
      a.click();
      a.remove();
      URL.revokeObjectURL(url);
    });
    acoes.append(botao);
    new MutationObserver(() => (botao.hidden = hw.hidden)).observe(hw, { attributes: true, attributeFilter: ["hidden"] });
  }

  montarPlataformas();
  montarGerador();
  observarCodigo();
  baixarCodigo();
})();
