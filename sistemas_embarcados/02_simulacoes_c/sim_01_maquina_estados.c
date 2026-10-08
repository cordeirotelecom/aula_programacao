/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_01 - Maquina de estados: semaforo com botao de pedestre.
   Maquina de estados = o sistema esta em UM estado e muda por eventos. */
#include <stdio.h>

typedef enum { VERDE, AMARELO, VERMELHO, N_ESTADOS } Estado;
typedef enum { EV_TEMPO, EV_PEDESTRE, N_EVENTOS } Evento;

static const char *nome_estado[N_ESTADOS] = { "VERDE   ", "AMARELO ", "VERMELHO" };
static const char *nome_evento[N_EVENTOS] = { "tempo   ", "pedestre" };

/* Tabela de transicoes: proximo = tabela[estado atual][evento] */
static const Estado tabela[N_ESTADOS][N_EVENTOS] = {
    /* VERDE    */ { AMARELO,  AMARELO  },
    /* AMARELO  */ { VERMELHO, VERMELHO },
    /* VERMELHO */ { VERDE,    VERMELHO }   /* pedestre no vermelho: continua */
};

int main(void)
{
    int i, j;
    Estado e = VERMELHO;
    /* sequencia de eventos simulada */
    Evento eventos[] = { EV_TEMPO, EV_PEDESTRE, EV_TEMPO, EV_TEMPO, EV_TEMPO, EV_PEDESTRE, EV_TEMPO };
    int n = (int)(sizeof(eventos) / sizeof(eventos[0]));

    printf("=== Tabela de transicoes ===\n");
    printf("%-10s", "estado");
    for (j = 0; j < N_EVENTOS; j++) printf("| %-9s", nome_evento[j]);
    printf("\n----------+----------+----------\n");
    for (i = 0; i < N_ESTADOS; i++) {
        printf("%-10s", nome_estado[i]);
        for (j = 0; j < N_EVENTOS; j++) printf("| %-9s", nome_estado[tabela[i][j]]);
        printf("\n");
    }

    printf("\n=== Execucao ===\n");
    printf("inicio: %s\n", nome_estado[e]);
    for (i = 0; i < n; i++) {
        Estado novo = tabela[e][eventos[i]];
        printf("evento %-8s : %s -> %s\n", nome_evento[eventos[i]], nome_estado[e], nome_estado[novo]);
        e = novo;
    }
    return 0;
}

/* EXERCICIOS:
   1) Inclua o estado PISCANTE (noite) e o evento EV_NOITE.
   2) Troque a tabela por um switch/case e compare a legibilidade.
   3) Desenhe o diagrama de estados no papel. */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_01_maquina_estados */
