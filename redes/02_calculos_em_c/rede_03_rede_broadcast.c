/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdint.h>

void mostrar_ip(uint32_t n)
{
    printf("%u.%u.%u.%u", (n >> 24) & 255u, (n >> 16) & 255u, (n >> 8) & 255u, n & 255u);
}

void mostrar_binario(uint32_t n)
{
    for (int bit = 31; bit >= 0; bit--) {
        printf("%u", (n >> bit) & 1u);
        if (bit % 8 == 0 && bit != 0) printf(".");
    }
}

/* AULA REDES 03 - Endereco de rede e broadcast
   Rede      = IP  AND  mascara      (zera os bits de host)
   Broadcast = Rede OR  wildcard     (coloca 1 em todos os bits de host) */
int main(void)
{
    unsigned int a, b, c, d, cidr;

    printf("Digite IP/CIDR (ex: 192.168.10.77/26): ");
    if (scanf("%u.%u.%u.%u/%u", &a, &b, &c, &d, &cidr) != 5
        || a > 255 || b > 255 || c > 255 || d > 255 || cidr > 32) {
        printf("Entrada invalida.\n");
        return 1;
    }

    uint32_t ip = (a << 24) | (b << 16) | (c << 8) | d;
    uint32_t mascara = (cidr == 0) ? 0 : (0xFFFFFFFFu << (32 - cidr));
    uint32_t rede = ip & mascara;                 /* AND */
    uint32_t broadcast = rede | ~mascara;         /* OR com o wildcard */

    printf("\nIP        : "); mostrar_binario(ip);        printf("  ("); mostrar_ip(ip); printf(")\n");
    printf("Mascara   : "); mostrar_binario(mascara);   printf("  ("); mostrar_ip(mascara); printf(")\n");
    printf("Rede      : "); mostrar_binario(rede);      printf("  ("); mostrar_ip(rede); printf(")\n");
    printf("Broadcast : "); mostrar_binario(broadcast); printf("  ("); mostrar_ip(broadcast); printf(")\n");

    return 0;
}

/* EXERCICIOS:
   1. Calcule a mao e confira: 10.1.2.3/8, 172.16.50.9/20, 192.168.1.130/25.
   2. O que acontece com a rede e o broadcast em /32?
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_03_rede_broadcast */
