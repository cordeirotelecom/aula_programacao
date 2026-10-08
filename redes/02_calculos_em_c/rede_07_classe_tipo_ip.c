/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA REDES 07 - Classe e tipo de endereco IP
   A classe (historica) depende do primeiro octeto:
     A: 1-126 (/8)   B: 128-191 (/16)   C: 192-223 (/24)
     D: 224-239 (multicast)   E: 240-255 (reservado)
   Faixas privadas (nao roteadas na Internet):
     10.0.0.0/8   172.16.0.0/12   192.168.0.0/16 */
int main(void)
{
    unsigned int a, b, c, d;

    printf("Digite um IP (ex: 172.20.5.9): ");
    if (scanf("%u.%u.%u.%u", &a, &b, &c, &d) != 4 || a > 255 || b > 255 || c > 255 || d > 255) {
        printf("IP invalido.\n");
        return 1;
    }

    if (a == 0)            printf("Classe: -  (rede 0, reservado)\n");
    else if (a < 127)      printf("Classe: A  (mascara padrao 255.0.0.0 /8)\n");
    else if (a == 127)     printf("Classe: -  (127.x.x.x e loopback, a propria maquina)\n");
    else if (a < 192)      printf("Classe: B  (mascara padrao 255.255.0.0 /16)\n");
    else if (a < 224)      printf("Classe: C  (mascara padrao 255.255.255.0 /24)\n");
    else if (a < 240)      printf("Classe: D  (multicast)\n");
    else                   printf("Classe: E  (reservado)\n");

    if (a == 10 || (a == 172 && b >= 16 && b <= 31) || (a == 192 && b == 168)) {
        printf("Tipo  : PRIVADO\n");
    } else if (a == 169 && b == 254) {
        printf("Tipo  : APIPA (sem DHCP, o Windows se auto-configura)\n");
    } else if (a == 127) {
        printf("Tipo  : LOOPBACK\n");
    } else {
        printf("Tipo  : PUBLICO (ou especial)\n");
    }

    return 0;
}

/* EXERCICIOS:
   1. Classifique: 8.8.8.8, 10.5.5.5, 172.32.0.1, 192.168.100.1, 169.254.10.10.
   2. 172.32.0.1 e privado? Por que o limite e 172.31?
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c rede_07_classe_tipo_ip */
