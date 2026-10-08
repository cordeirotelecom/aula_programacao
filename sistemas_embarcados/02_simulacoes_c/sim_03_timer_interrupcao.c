/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_03 - Timer periodico + interrupcao (ISR) simulados.
   Em um microcontrolador real, o hardware chama a ISR sozinho a cada estouro do timer.
   Aqui simulamos isso chamando a funcao dentro de um laco. */
#include <stdio.h>

/* volatile: avisa ao compilador que outra "parte" (a ISR) altera a variavel */
static volatile int flag_tick = 0;
static volatile unsigned long ticks = 0;

/* ISR: deve ser CURTA. So marca a flag e conta. */
static void timer_isr(void)
{
    ticks++;
    flag_tick = 1;
}

int main(void)
{
    int t_ms;
    int leds = 0;
    printf("=== Timer de 1 ms; tarefa do loop principal a cada 100 ms ===\n");
    for (t_ms = 1; t_ms <= 500; t_ms++) {
        timer_isr();                    /* hardware dispara a interrupcao */

        /* loop principal: trata o evento fora da ISR */
        if (flag_tick) {
            flag_tick = 0;
            if (ticks % 100 == 0) {
                leds = !leds;
                printf("t=%3lu ms  LED %s\n", ticks, leds ? "ACESO  [*]" : "APAGADO [ ]");
            }
        }
    }
    printf("\nPor que a ISR deve ser curta?\n");
    printf(" - Enquanto ela roda, outras interrupcoes esperam (ou se perdem).\n");
    printf(" - Nao use printf, delay ou laco longo dentro dela.\n");
    printf(" - Padrao: ISR marca uma flag; o loop principal faz o trabalho pesado.\n");
    return 0;
}

/* EXERCICIOS:
   1) Troque o LED para piscar a cada 250 ms.
   2) Conte quantos ticks existem em 1 segundo (1000).
   3) Remova o volatile e pesquise o que pode dar errado com otimizacao. */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_03_timer_interrupcao */
