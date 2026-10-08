/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_05 - PWM em ASCII: duty cycle e tensao media.
   PWM = pulsos liga/desliga rapidos. Tensao media = Vcc * duty. */
#include <stdio.h>

#define VCC 5.0
#define PERIODO 20   /* passos por periodo do PWM */

static void desenhar(int duty_pct)
{
    int ligado = PERIODO * duty_pct / 100;
    int p, i;
    printf("duty %3d%%  ", duty_pct);
    for (p = 0; p < 3; p++) {           /* 3 periodos */
        for (i = 0; i < PERIODO; i++)
            printf("%c", i < ligado ? '#' : '_');
    }
    printf("  Vmedia = %.2f V\n", VCC * duty_pct / 100.0);
}

int main(void)
{
    int d;
    printf("=== PWM com Vcc = %.1f V (3 periodos; # = nivel alto, _ = nivel baixo) ===\n\n", VCC);
    for (d = 0; d <= 100; d += 25) desenhar(d);

    printf("\n=== Brilho de um LED (0 a 255, como analogWrite) ===\n");
    printf("valor  duty    barra\n");
    for (d = 0; d <= 255; d += 51) {
        int pct = d * 100 / 255;
        int k;
        printf("%4d  %3d%%    ", d, pct);
        for (k = 0; k < pct / 5; k++) printf("=");
        printf("\n");
    }
    printf("\nServo: pulso de 1 ms a 2 ms a cada 20 ms -> duty de 5%% a 10%%.\n");
    return 0;
}

/* EXERCICIOS:
   1) Calcule a Vmedia para duty 30% com Vcc 3.3 V.
   2) Mude PERIODO para 10 e veja a resolucao do duty.
   3) Desenhe o duty de 7,5% (servo no centro). */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_05_pwm_ascii */
