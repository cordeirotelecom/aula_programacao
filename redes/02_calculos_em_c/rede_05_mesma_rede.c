/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdint.h>

/* Le um IP no formato a.b.c.d e devolve em um numero de 32 bits.
   Retorna 0 se deu certo e 1 se o IP e invalido. */
int ler_ip(uint32_t *resultado)
{
    unsigned int a, b, c, d;
    if (scanf("%u.%u.%u.%u", &a, &b, &c, &d) != 4 || a > 255 || b > 255 || c > 255 || d > 255) {
        return 1;
    }
    *resultado = (a << 24) | (b << 16) | (c << 8) | d;
    return 0;
}

/* AULA REDES 05 - Duas maquinas estao na mesma rede?
   Aplica-se a mascara nos dois IPs. Se o resultado for igual, elas se
   comunicam direto; se for diferente, precisam de um roteador (gateway). */
int main(void)
{
    uint32_t ip1, ip2;
    unsigned int cidr;

    printf("IP da maquina 1: ");
    if (ler_ip(&ip1)) { printf("IP invalido.\n"); return 1; }
    printf("IP da maquina 2: ");
    if (ler_ip(&ip2)) { printf("IP invalido.\n"); return 1; }
    printf("Prefixo CIDR (ex: 24): ");
    if (scanf("%u", &cidr) != 1 || cidr > 32) { printf("Prefixo invalido.\n"); return 1; }

    uint32_t mascara = (cidr == 0) ? 0 : (0xFFFFFFFFu << (32 - cidr));

    if ((ip1 & mascara) == (ip2 & mascara)) {
        printf("MESMA rede: comunicacao direta (switch).\n");
    } else {
        printf("Redes DIFERENTES: o trafego precisa passar por um roteador.\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. 192.168.1.10 e 192.168.1.200 com /24 e com /25. Por que muda?
   2. Mostre tambem o endereco da rede de cada maquina.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_05_mesma_rede */
