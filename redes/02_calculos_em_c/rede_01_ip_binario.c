/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA REDES 01 - IP em binario
   Um IPv4 tem 4 octetos (a.b.c.d) de 8 bits cada: 32 bits no total.
   Para converter, divide-se por 2 (ou compara-se bit a bit). */
int main(void)
{
    unsigned int octeto[4];

    printf("Digite um IP (ex: 192.168.10.25): ");
    if (scanf("%u.%u.%u.%u", &octeto[0], &octeto[1], &octeto[2], &octeto[3]) != 4) {
        printf("IP invalido.\n");
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        if (octeto[i] > 255) {
            printf("Cada octeto deve estar entre 0 e 255.\n");
            return 1;
        }
    }

    for (int i = 0; i < 4; i++) {
        printf("%3u = ", octeto[i]);
        for (int bit = 7; bit >= 0; bit--) {
            printf("%u", (octeto[i] >> bit) & 1u);   /* pega o bit na posicao */
        }
        printf("\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Converta 10.0.0.1, 172.16.5.9 e 255.255.255.0 e confira com a mao.
   2. Mostre os octetos separados por pontos na mesma linha.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_01_ip_binario */
