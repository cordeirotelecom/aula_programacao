/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_10 - Watchdog (reseta se o programa travar) e debounce de botao.
   Parte A: o programa "alimenta" o watchdog; na iteracao 6 ele trava.
   Parte B: botao com ruido (trepidacao) filtrado por contador. */
#include <stdio.h>

#define TIMEOUT 3   /* ticks sem alimentar -> reset */

static int wdt_contador = TIMEOUT;

static void wdt_alimentar(void) { wdt_contador = TIMEOUT; }

static int wdt_tick(void)   /* retorna 1 se estourou */
{
    wdt_contador--;
    return wdt_contador <= 0;
}

static void parte_watchdog(void)
{
    int tick, resets = 0, travado = 0;
    printf("=== A) Watchdog: timeout de %d ticks ===\n", TIMEOUT);
    for (tick = 1; tick <= 12; tick++) {
        if (tick == 6) travado = 1;           /* bug: o laco principal trava */
        if (!travado) {
            wdt_alimentar();
            printf("tick %2d: programa OK, alimentou o watchdog\n", tick);
        } else {
            printf("tick %2d: programa TRAVADO (contador=%d)\n", tick, wdt_contador - 1);
        }
        if (wdt_tick()) {
            printf("tick %2d: *** WATCHDOG ESTOUROU -> RESET DO SISTEMA ***\n", tick);
            resets++;
            travado = 0;                      /* depois do reset volta a funcionar */
            wdt_alimentar();
        }
    }
    printf("Resets: %d\n\n", resets);
}

static void parte_debounce(void)
{
    /* leitura bruta: 1 = pressionado. O botao "treme" ao apertar e ao soltar */
    const int bruto[] = { 0,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0 };
    int n = (int)(sizeof(bruto) / sizeof(bruto[0]));
    int i, estavel = 0, cont = 0, eventos = 0;
    const int LIMITE = 4;   /* leituras iguais seguidas para aceitar */

    printf("=== B) Debounce: exige %d leituras iguais seguidas ===\n", LIMITE);
    printf(" i | bruto | estavel | evento\n");
    printf("---+-------+---------+-------\n");
    for (i = 0; i < n; i++) {
        const char *ev = "";
        if (bruto[i] != estavel) {
            cont++;
            if (cont >= LIMITE) {
                estavel = bruto[i];
                cont = 0;
                ev = estavel ? "PRESSIONADO" : "SOLTO";
                eventos++;
            }
        } else {
            cont = 0;
        }
        printf("%2d |   %d   |    %d    | %s\n", i, bruto[i], estavel, ev);
    }
    printf("Eventos validos: %d (sem debounce teriamos 8)\n", eventos);
}

int main(void)
{
    parte_watchdog();
    parte_debounce();
    return 0;
}

/* EXERCICIOS:
   1) Mude TIMEOUT para 5 e veja quando o reset acontece.
   2) Mude LIMITE para 2 e 8; qual o efeito na resposta e no ruido?
   3) Por que o watchdog nao deve ser alimentado dentro de uma ISR? */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_10_watchdog_debounce */
