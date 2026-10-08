/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA REDES 08 - Calculo passo a passo (igual ao do papel)
   O programa NARRA cada passo, para voce aprender o metodo:
   octeto interessante, tamanho do bloco, rede, broadcast e hosts. */
int main(void)
{
    unsigned int ip[4], cidr;

    printf("Digite IP/CIDR (ex: 192.168.10.77/26): ");
    if (scanf("%u.%u.%u.%u/%u", &ip[0], &ip[1], &ip[2], &ip[3], &cidr) != 5
        || ip[0] > 255 || ip[1] > 255 || ip[2] > 255 || ip[3] > 255 || cidr > 31) {
        printf("Entrada invalida (use CIDR de 0 a 31).\n");
        return 1;
    }

    unsigned int k = cidr / 8;       /* octetos inteiros de mascara (255) */
    unsigned int r = cidr % 8;       /* bits ligados no octeto interessante */
    unsigned int bloco = 1u << (8 - r);
    unsigned int mascara[4], rede[4], broadcast[4];

    printf("\nPASSO 1 - /%u = %u bits de rede e %u bits de host.\n", cidr, cidr, 32 - cidr);

    printf("PASSO 2 - %u = %u octeto(s) cheio(s) de 8 bits + %u bit(s) no proximo.\n", cidr, k, r);

    for (unsigned int i = 0; i < 4; i++) {
        mascara[i] = (i < k) ? 255u : (i == k ? 256u - bloco : 0u);
    }
    /* quando r == 0 o octeto interessante tem mascara 0 e bloco 256 */
    printf("         Mascara = %u.%u.%u.%u\n", mascara[0], mascara[1], mascara[2], mascara[3]);

    printf("PASSO 3 - Octeto interessante: o %uo (mascara %u).\n", k + 1, mascara[k]);
    printf("         Bloco = 256 - %u = %u\n", mascara[k], bloco);

    unsigned int multiplo = ip[k] / bloco;      /* divisao inteira */
    for (unsigned int i = 0; i < 4; i++) {
        rede[i]      = (i < k) ? ip[i] : (i == k ? multiplo * bloco : 0u);
        broadcast[i] = (i < k) ? ip[i] : (i == k ? multiplo * bloco + bloco - 1 : 255u);
    }

    printf("PASSO 4 - Rede: %u / %u = %u (inteiro); %u x %u = %u\n",
           ip[k], bloco, multiplo, multiplo, bloco, rede[k]);
    printf("         REDE = %u.%u.%u.%u/%u\n", rede[0], rede[1], rede[2], rede[3], cidr);

    printf("PASSO 5 - Broadcast: %u + %u - 1 = %u\n", rede[k], bloco, broadcast[k]);
    printf("         BROADCAST = %u.%u.%u.%u\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3]);

    if (cidr == 31) {
        printf("PASSO 6 - /31 e especial (enlace ponto a ponto): 2 enderecos usaveis.\n");
    } else {
        unsigned long long hosts = (1ull << (32 - cidr)) - 2;
        printf("PASSO 6 - Primeiro host = %u.%u.%u.%u\n", rede[0], rede[1], rede[2], rede[3] + 1);
        printf("         Ultimo host   = %u.%u.%u.%u\n", broadcast[0], broadcast[1], broadcast[2], broadcast[3] - 1);
        printf("         Hosts = 2^%u - 2 = %llu\n", 32 - cidr, hosts);
    }

    return 0;
}

/* EXERCICIOS:
   1. Resolva no papel e confira: 192.168.1.130/25, 10.4.200.33/18, 172.20.100.5/29.
   2. Explique com suas palavras por que o bloco e 256 menos a mascara.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_08_passo_a_passo */
