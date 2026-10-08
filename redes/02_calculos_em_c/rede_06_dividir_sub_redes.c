/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdint.h>

void mostrar_ip(uint32_t n)
{
    printf("%u.%u.%u.%u", (n >> 24) & 255u, (n >> 16) & 255u, (n >> 8) & 255u, n & 255u);
}

/* AULA REDES 06 - Dividir uma rede em sub-redes
   Pegamos bits emprestados da parte de host. Com N bits emprestados
   temos 2^N sub-redes. Cada sub-rede tem 2^(32 - novo CIDR) enderecos. */
int main(void)
{
    unsigned int a, b, c, d, cidr, quantidade;

    printf("Digite a rede/CIDR (ex: 192.168.10.0/24): ");
    if (scanf("%u.%u.%u.%u/%u", &a, &b, &c, &d, &cidr) != 5
        || a > 255 || b > 255 || c > 255 || d > 255 || cidr > 30) {
        printf("Entrada invalida (use CIDR de 0 a 30).\n");
        return 1;
    }
    printf("Quantas sub-redes? ");
    if (scanf("%u", &quantidade) != 1 || quantidade < 1 || quantidade > 1024) {
        printf("Quantidade invalida (1 a 1024).\n");
        return 1;
    }

    unsigned int bits = 0;
    while ((1u << bits) < quantidade) bits++;     /* menor N tal que 2^N >= quantidade */
    unsigned int novo_cidr = cidr + bits;
    if (novo_cidr > 30) {
        printf("Nao e possivel: sobrariam menos de 2 bits de host.\n");
        return 1;
    }

    uint32_t mascara_antiga = (cidr == 0) ? 0 : (0xFFFFFFFFu << (32 - cidr));
    uint32_t base = ((a << 24) | (b << 16) | (c << 8) | d) & mascara_antiga;
    uint32_t tamanho = 1u << (32 - novo_cidr);
    unsigned int total = 1u << bits;

    printf("\nBits emprestados: %u  -> %u sub-redes /%u (%u hosts cada)\n\n",
           bits, total, novo_cidr, tamanho - 2);
    printf("%-4s %-18s %-16s %-16s %-16s\n", "N", "Rede", "Primeiro host", "Ultimo host", "Broadcast");

    for (unsigned int i = 0; i < total; i++) {
        uint32_t rede = base + i * tamanho;
        uint32_t broadcast = rede + tamanho - 1;
        printf("%-4u ", i + 1);
        mostrar_ip(rede);          printf("/%u    ", novo_cidr);
        mostrar_ip(rede + 1);      printf("   ");
        mostrar_ip(broadcast - 1); printf("   ");
        mostrar_ip(broadcast);     printf("\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Divida 192.168.10.0/24 em 4 e depois em 6 sub-redes. Compare.
   2. Divida 10.0.0.0/8 em 100 sub-redes: qual o novo CIDR?
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_06_dividir_sub_redes */
