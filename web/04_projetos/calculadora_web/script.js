// Elaborado pelo Prof. Vagner Cordeiro
// PROJETO - Calculadora: guarda a conta como texto e calcula ao pressionar "=".
const visor = document.getElementById("visor");
let conta = "";

function calcular(expressao) {
  // aceita somente numeros, operadores e ponto (evita executar codigo digitado)
  if (!/^[0-9+\-*/. ]+$/.test(expressao)) return "Erro";
  try {
    const resultado = Function('"use strict"; return (' + expressao + ")")();
    return Number.isFinite(resultado) ? String(Number(resultado.toFixed(8))) : "Erro";
  } catch (erro) {
    return "Erro";
  }
}

document.querySelectorAll("button").forEach((botao) => {
  botao.addEventListener("click", () => {
    const tecla = botao.dataset.tecla;
    if (tecla === "C") {
      conta = "";
    } else if (tecla === "=") {
      conta = calcular(conta);
      if (conta === "Erro") { visor.textContent = "Erro"; conta = ""; return; }
    } else {
      conta += tecla;
    }
    visor.textContent = conta === "" ? "0" : conta;
  });
});

// EXERCICIOS:
// 1. Adicione o botao de apagar o ultimo digito (conta = conta.slice(0, -1)).
// 2. Faca a calculadora tambem funcionar com o teclado (evento "keydown").
// 3. Adicione o botao de porcentagem.
