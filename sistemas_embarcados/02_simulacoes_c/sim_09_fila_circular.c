/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_09 - Buffer circular (fila) com produtor/consumidor.
   A "ISR" produz bytes recebidos; o loop principal consome. */
#include <stdio.h>

#define TAM 4   /* guarda no maximo TAM-1 itens (1 posicao sempre livre) */

static volatile unsigned char buf[TAM];
static volatile int head = 0;   /* onde a ISR escreve */
static volatile int tail = 0;   /* de onde o main le */
static int perdidos = 0;

static int cheio(void) { return ((head + 1) % TAM) == tail; }
static int vazio(void) { return head == tail; }

static void mostrar(void)
{
    int i;
    printf("   [");
    for (i = 0; i < TAM; i++) {
        if (i == head && i == tail) printf(" HT");
        else if (i == head) printf(" H ");
        else if (i == tail) printf(" T ");
        else printf("   ");
    }
    printf("]  itens=%d\n", (head - tail + TAM) % TAM);
}

/* ISR simulada: chega um byte pela UART */
static void uart_isr(unsigned char b)
{
    if (cheio()) {
        perdidos++;
        printf("ISR   : '%c' PERDIDO (fila cheia)\n", b);
    } else {
        buf[head] = b;
        head = (head + 1) % TAM;
        printf("ISR   : guardou '%c'\n", b);
    }
    mostrar();
}

static void consumir(void)
{
    if (vazio()) {
        printf("MAIN  : fila vazia\n");
    } else {
        printf("MAIN  : leu '%c'\n", buf[tail]);
        tail = (tail + 1) % TAM;
    }
    mostrar();
}

int main(void)
{
    const char *chegada = "ABCDE";
    int i;
    printf("=== Fila circular de %d posicoes (H=head/escrita, T=tail/leitura) ===\n", TAM);
    mostrar();
    for (i = 0; i < 3; i++) uart_isr((unsigned char)chegada[i]);   /* rajada: ABC */
    consumir();
    uart_isr((unsigned char)chegada[3]);                            /* D */
    uart_isr((unsigned char)chegada[4]);                            /* E: cheia */
    consumir(); consumir(); consumir(); consumir();
    printf("\nBytes perdidos: %d\n", perdidos);
    return 0;
}

/* EXERCICIOS:
   1) Aumente TAM para 8 e veja se algum byte se perde.
   2) Faca uma funcao que retorna quantos itens ha na fila.
   3) Pense: por que head e tail evitam a necessidade de mover os dados? */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_09_fila_circular */
