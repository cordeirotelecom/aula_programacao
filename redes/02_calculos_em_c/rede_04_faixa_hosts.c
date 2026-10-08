/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdint.h>

void mostrar_ip(uint32_t n)
{
    printf("%u.%u.%u.%u", (n >> 24) & 255u, (n >> 16) & 255u, (n >> 8) & 255u, n & 255u);
}

/* AULA REDES 04 - Faixa de hosts e quantidade de maquinas
   Primeiro host = rede + 1       Ultimo host = broadcast - 1
   Hosts utilizaveis = 2^(bits de host) - 2  (tira rede e broadcast) */
int main(void)
{
    unsigned int a, b, c, d, cidr;

    printf("Digite IP/CIDR (ex: 172.16.40.5/21): ");
    if (scanf("%u.%u.%u.%u/%u", &a, &b, &c, &d, &cidr) != 5
        || a > 255 || b > 255 || c > 255 || d > 255 || cidr > 32) {
        printf("Entrada invalida.\n");
        return 1;
    }

    uint32_t ip = (a << 24) | (b << 16) | (c << 8) | d;
    uint32_t mascara = (cidr == 0) ? 0 : (0xFFFFFFFFu << (32 - cidr));
    uint32_t rede = ip & mascara;
    uint32_t broadcast = rede | ~mascara;
    unsigned long long total = 1ull << (32 - cidr);

    printf("Rede      : "); mostrar_ip(rede); printf("/%u\n", cidr);
    printf("Broadcast : "); mostrar_ip(broadcast); printf("\n");

    if (cidr >= 31) {                              /* casos especiais */
        printf("Prefixo /%u: nao ha faixa tradicional de hosts (/31 = enlace ponto a ponto).\n", cidr);
    } else {
        printf("Primeiro host: "); mostrar_ip(rede + 1); printf("\n");
        printf("Ultimo host  : "); mostrar_ip(broadcast - 1); printf("\n");
        printf("Hosts utilizaveis: %llu\n", total - 2);
    }

    return 0;
}

/* EXERCICIOS:
   1. Quantos hosts tem a rede 192.168.0.0/22?
   2. Qual a faixa de 10.10.10.200/27?
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_04_faixa_hosts */
