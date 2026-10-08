/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_08 - I2C (start, endereco, ACK, dado, stop) e SPI modo 0 bit a bit.
   Tudo desenhado em ASCII. Nada de hardware: so a logica dos protocolos. */
#include <stdio.h>

static void i2c_byte(const char *nome, unsigned char b, int ack)
{
    int i;
    printf("  %-9s: ", nome);
    for (i = 7; i >= 0; i--) printf("%d ", (b >> i) & 1);   /* MSB primeiro */
    printf("| ACK=%d (%s)\n", ack, ack == 0 ? "escravo respondeu" : "sem resposta");
}

static void exemplo_i2c(void)
{
    unsigned char addr = 0x48;   /* endereco de 7 bits, ex: sensor de temperatura */
    unsigned char escrita = (unsigned char)((addr << 1) | 0);   /* bit R/W = 0 -> escrever */
    printf("=== I2C: escrever 0x2A no escravo 0x48 ===\n");
    printf("  SDA e SCL ficam em 1 (pull-up). O mestre gera o clock (SCL).\n");
    printf("  START    : SDA cai de 1 para 0 enquanto SCL = 1\n");
    i2c_byte("end+W", escrita, 0);
    i2c_byte("dado", 0x2A, 0);
    printf("  STOP     : SDA sobe de 0 para 1 enquanto SCL = 1\n");
    printf("  Resumo   : S | 0x%02X (0x%02X<<1 + W) | A | 0x2A | A | P\n\n", escrita, addr);
}

static void exemplo_spi(void)
{
    unsigned char mosi = 0xA5, miso = 0x3C, rx_mestre = 0, rx_escravo = 0;
    int i;
    printf("=== SPI modo 0 (CPOL=0, CPHA=0): troca simultanea de 0xA5 e 0x3C ===\n");
    printf("  bit | SCK | MOSI | MISO\n");
    printf("  ----+-----+------+-----\n");
    for (i = 7; i >= 0; i--) {
        int m = (mosi >> i) & 1, s = (miso >> i) & 1;
        printf("   %d  |  _  |  %d   |  %d     (dado preparado)\n", i, m, s);
        printf("      | _|- |  %d   |  %d     (borda de subida: amostra)\n", m, s);
        rx_escravo = (unsigned char)((rx_escravo << 1) | m);
        rx_mestre  = (unsigned char)((rx_mestre << 1) | s);
    }
    printf("  Escravo recebeu 0x%02X (mestre enviou 0x%02X)\n", rx_escravo, mosi);
    printf("  Mestre  recebeu 0x%02X (escravo enviou 0x%02X)\n", rx_mestre, miso);
    printf("  O sinal CS (chip select) fica em 0 durante toda a troca.\n");
}

int main(void)
{
    exemplo_i2c();
    exemplo_spi();
    return 0;
}

/* EXERCICIOS:
   1) Mude o endereco I2C para 0x68 e mostre o byte de endereco.
   2) Simule uma leitura I2C (bit R/W = 1).
   3) Mude para SPI modo 1 (amostra na borda de descida) e explique a diferenca. */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_08_i2c_spi */
