/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_04 - Escalonador de RTOS simplificado (tempo discreto, 1 tick = 1 passo).
   3 tarefas periodicas. Parte 1: prioridade preemptiva. Parte 2: round robin. */
#include <stdio.h>

#define N 3
#define TICKS 24

typedef struct {
    const char *nome;
    char letra;
    int periodo;     /* a cada quantos ticks a tarefa fica pronta */
    int custo;       /* ticks de CPU por execucao */
    int prioridade;  /* maior numero = mais importante */
    int restante;    /* trabalho que falta */
} Tarefa;

static void inicializar(Tarefa t[N])
{
    Tarefa base[N] = {
        { "Sensor ", 'S', 4,  1, 3, 0 },
        { "Display", 'D', 8,  3, 2, 0 },
        { "Log    ", 'L', 12, 4, 1, 0 }
    };
    int i;
    for (i = 0; i < N; i++) t[i] = base[i];
}

/* modo 0 = prioridade ; modo 1 = round robin */
static void simular(int modo)
{
    Tarefa t[N];
    char linha[N + 1][TICKS + 1];
    int tick, i, atual = -1, rr = 0;

    inicializar(t);
    for (i = 0; i <= N; i++) {
        int k;
        for (k = 0; k < TICKS; k++) linha[i][k] = '.';
        linha[i][TICKS] = '\0';
    }

    for (tick = 0; tick < TICKS; tick++) {
        int escolhida = -1;
        for (i = 0; i < N; i++)
            if (tick % t[i].periodo == 0) t[i].restante += t[i].custo;

        if (modo == 0) {
            for (i = 0; i < N; i++)
                if (t[i].restante > 0 && (escolhida < 0 || t[i].prioridade > t[escolhida].prioridade))
                    escolhida = i;
            /* preempcao: troca de tarefa com a anterior ainda inacabada */
            if (atual >= 0 && escolhida >= 0 && escolhida != atual && t[atual].restante > 0)
                printf("  tick %2d: PREEMPCAO! %s interrompe %s\n", tick, t[escolhida].nome, t[atual].nome);
        } else {
            for (i = 0; i < N && escolhida < 0; i++) {
                int c = (rr + i) % N;
                if (t[c].restante > 0) escolhida = c;
            }
            if (escolhida >= 0) rr = (escolhida + 1) % N;
        }

        if (escolhida >= 0) {
            t[escolhida].restante--;
            linha[escolhida][tick] = '#';
            linha[N][tick] = t[escolhida].letra;
        } else {
            linha[N][tick] = '-';
        }
        atual = escolhida;
    }

    printf("  dezenas   ");
    for (i = 0; i < TICKS; i++) printf("%d", i / 10);
    printf("\n  tempo     ");
    for (i = 0; i < TICKS; i++) printf("%d", i % 10);
    printf("\n");
    for (i = 0; i < N; i++)
        printf("  %s : %s\n", t[i].nome, linha[i]);
    printf("  CPU     : %s\n", linha[N]);
    for (i = 0; i < N; i++)
        if (t[i].restante > 0)
            printf("  ATENCAO: %s com %d tick(s) pendente(s) no fim!\n", t[i].nome, t[i].restante);
}

int main(void)
{
    printf("=== Tarefas: Sensor(T=4,C=1,P=3) Display(T=8,C=3,P=2) Log(T=12,C=4,P=1) ===\n");
    printf("\n--- Escalonamento por PRIORIDADE preemptivo ---\n");
    simular(0);
    printf("\n--- Escalonamento ROUND ROBIN (1 tick por tarefa) ---\n");
    simular(1);
    printf("\nLegenda: # = executando, . = esperando/inativa, S/D/L = quem usa a CPU, - = ociosa\n");
    return 0;
}

/* EXERCICIOS:
   1) Mude as prioridades e observe qual tarefa passa a atrasar.
   2) Calcule a utilizacao da CPU: soma de custo/periodo.
   3) Aumente o custo do Log para 8 e veja o que acontece. */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_04_escalonador_rtos */
