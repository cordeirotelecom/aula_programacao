/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>
#include <stdint.h>

/* Mostra um numero de 32 bits como a.b.c.d */
void mostrar_ip(uint32_t n)
{
    printf("%u.%u.%u.%u", (n >> 24) & 255u, (n >> 16) & 255u, (n >> 8) & 255u, n & 255u);
}

/* Mostra os 32 bits em 4 grupos de 8 */
void mostrar_binario(uint32_t n)
{
    for (int bit = 31; bit >= 0; bit--) {
        printf("%u", (n >> bit) & 1u);
        if (bit % 8 == 0 && bit != 0) printf(".");
    }
}

/* AULA REDES 02 - Mascara de rede a partir do CIDR
   /24 significa: os 24 primeiros bits sao 1 (parte da rede) e os 8
   ultimos sao 0 (parte dos hosts).  Mascara = 11111111.11111111.11111111.00000000 */
int main(void)
{
    unsigned int cidr;

    printf("Digite o prefixo CIDR (0 a 32), ex: 26: ");
    if (scanf("%u", &cidr) != 1 || cidr > 32) {
        printf("Prefixo invalido.\n");
        return 1;
    }

    uint32_t mascara = (cidr == 0) ? 0 : (0xFFFFFFFFu << (32 - cidr));
    uint32_t curinga = ~mascara;                     /* wildcard: bits invertidos */
    uint64_t enderecos = 1ull << (32 - cidr);        /* 2 elevado a bits de host */

    printf("Mascara decimal : "); mostrar_ip(mascara); printf("\n");
    printf("Mascara binaria : "); mostrar_binario(mascara); printf("\n");
    printf("Wildcard        : "); mostrar_ip(curinga); printf("\n");
    printf("Total de enderecos: %llu\n", (unsigned long long)enderecos);
    if (cidr <= 30) {
        printf("Hosts utilizaveis : %llu\n", (unsigned long long)(enderecos - 2));
    }

    return 0;
}

/* EXERCICIOS:
   1. Teste /8, /16, /24, /25, /30 e anote os resultados.
   2. Qual CIDR da 62 hosts utilizaveis? E 510?
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_02_mascara_cidr */
