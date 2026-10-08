// Elaborado pelo Prof. Vagner Cordeiro
// PROJETO - Lista de tarefas: adicionar, marcar como feita e remover.
// Tudo fica salvo no localStorage.
const formulario = document.getElementById("formulario");
const entrada = document.getElementById("entrada");
const lista = document.getElementById("lista");
const resumo = document.getElementById("resumo");

let tarefas = JSON.parse(localStorage.getItem("tarefas")) || [];

function salvar() {
  localStorage.setItem("tarefas", JSON.stringify(tarefas));
}

function desenhar() {
  lista.innerHTML = "";
  tarefas.forEach((tarefa, indice) => {
    const li = document.createElement("li");
    if (tarefa.feita) li.classList.add("feita");

    const texto = document.createElement("span");
    texto.textContent = tarefa.texto;
    li.addEventListener("click", () => {
      tarefa.feita = !tarefa.feita;
      salvar();
      desenhar();
    });

    const remover = document.createElement("button");
    remover.textContent = "X";
    remover.addEventListener("click", (evento) => {
      evento.stopPropagation();            // nao marca como feita ao remover
      tarefas.splice(indice, 1);
      salvar();
      desenhar();
    });

    li.append(texto, remover);
    lista.appendChild(li);
  });

  const feitas = tarefas.filter(t => t.feita).length;
  resumo.textContent = `${feitas} de ${tarefas.length} tarefa(s) concluida(s)`;
}

formulario.addEventListener("submit", (evento) => {
  evento.preventDefault();
  const texto = entrada.value.trim();
  if (texto === "") return;
  tarefas.push({ texto: texto, feita: false });
  entrada.value = "";
  salvar();
  desenhar();
});

desenhar();

// EXERCICIOS:
// 1. Adicione um botao "Limpar concluidas".
// 2. Impeça tarefas repetidas.
// 3. Adicione um campo de prioridade (alta/baixa) e pinte a tarefa conforme ela.
