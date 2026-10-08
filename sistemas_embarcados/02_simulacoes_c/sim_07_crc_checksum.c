/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_07 - Checksum simples e CRC-8 (polinomio 0x07) bit a bit.
   Servem para detectar erros de transmissao. */
#include <stdio.h>

static unsigned char checksum(const unsigned char *d, int n)
{
    unsigned char s = 0;
    int i;
    for (i = 0; i < n; i++) s = (unsigned char)(s + d[i]);   /* soma modulo 256 */
    return s;
}

/* CRC-8: polinomio x^8 + x^2 + x + 1 (0x07), valor inicial 0 */
static unsigned char crc8(const unsigned char *d, int n)
{
    unsigned char crc = 0;
    int i, b;
    for (i = 0; i < n; i++) {
        crc = (unsigned char)(crc ^ d[i]);
        for (b = 0; b < 8; b++) {
            if (crc & 0x80) crc = (unsigned char)((crc << 1) ^ 0x07);
            else            crc = (unsigned char)(crc << 1);
        }
    }
    return crc;
}

static void mostrar(const char *rotulo, const unsigned char *d, int n)
{
    int i;
    printf("%-10s dados:", rotulo);
    for (i = 0; i < n; i++) printf(" %02X", d[i]);
    printf("  | checksum=%02X  crc8=%02X\n", checksum(d, n), crc8(d, n));
}

int main(void)
{
    unsigned char msg[5] = { 0x48, 0x45, 0x4C, 0x4C, 0x4F };   /* "HELLO" */
    unsigned char ruim[5] = { 0x48, 0x45, 0x4C, 0x4C, 0x4F };
    unsigned char c1 = checksum(msg, 5), c2 = crc8(msg, 5);

    printf("=== Mensagem original e mensagem com 1 bit alterado ===\n");
    ruim[2] = (unsigned char)(ruim[2] ^ 0x04);   /* inverte o bit 2 do terceiro byte */
    mostrar("original", msg, 5);
    mostrar("alterada", ruim, 5);
    printf("\nChecksum %s o erro.\n", checksum(ruim, 5) != c1 ? "DETECTOU" : "NAO detectou");
    printf("CRC-8    %s o erro.\n", crc8(ruim, 5) != c2 ? "DETECTOU" : "NAO detectou");

    /* troca de ordem de dois bytes: checksum e cego, CRC percebe */
    {
        unsigned char troca[5] = { 0x48, 0x45, 0x4C, 0x4F, 0x4C };
        printf("\n=== Dois ultimos bytes trocados de lugar (HELLO -> HELOL) ===\n");
        mostrar("trocada", troca, 5);
        printf("Checksum %s | CRC-8 %s\n",
               checksum(troca, 5) != c1 ? "DETECTOU" : "NAO detectou",
               crc8(troca, 5) != c2 ? "DETECTOU" : "NAO detectou");
    }
    return 0;
}

/* EXERCICIOS:
   1) Altere outro bit e confira se o CRC-8 detecta.
   2) Procure dois bytes diferentes que dao o mesmo checksum.
   3) Pesquise CRC-16 e CRC-32 e onde sao usados (Ethernet, Modbus). */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_07_crc_checksum */
