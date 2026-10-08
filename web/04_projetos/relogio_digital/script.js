// Elaborado pelo Prof. Vagner Cordeiro
// PROJETO - Relogio digital com data e saudacao conforme o horario.
const hora = document.getElementById("hora");
const data = document.getElementById("data");
const saudacao = document.getElementById("saudacao");

function doisDigitos(n) {
  return String(n).padStart(2, "0");
}

function atualizar() {
  const agora = new Date();
  hora.textContent = `${doisDigitos(agora.getHours())}:${doisDigitos(agora.getMinutes())}:${doisDigitos(agora.getSeconds())}`;
  data.textContent = agora.toLocaleDateString("pt-BR", { weekday: "long", day: "numeric", month: "long", year: "numeric" });

  const h = agora.getHours();
  if (h < 12) saudacao.textContent = "Bom dia!";
  else if (h < 18) saudacao.textContent = "Boa tarde!";
  else saudacao.textContent = "Boa noite!";
  document.body.classList.toggle("dia", h >= 6 && h < 18);
}

atualizar();
setInterval(atualizar, 1000);

// EXERCICIOS:
// 1. Mostre tambem o texto "AM" ou "PM" (formato 12 horas).
// 2. Adicione um botao que alterna entre formato 12 h e 24 h.
// 3. Crie um alarme: avise quando chegar um horario escolhido.
