/* Elaborado pelo Prof. Vagner Cordeiro */
/* sim_11 - Bits e registradores: mascaras, set/clear/toggle em um registrador GPIO simulado.
   Em microcontroladores reais, o registrador fica num endereco fixo e e volatile. */
#include <stdio.h>
#include <stdint.h>

/* Registrador simulado de 8 pinos (PORTB). volatile = o hardware pode mudar o valor. */
static volatile uint8_t PORTB = 0x00;

#define BIT(n)        (1u << (n))
#define SET_BIT(r, n)    ((r) = (uint8_t)((r) | BIT(n)))
#define CLEAR_BIT(r, n)  ((r) = (uint8_t)((r) & ~BIT(n)))
#define TOGGLE_BIT(r, n) ((r) = (uint8_t)((r) ^ BIT(n)))
#define READ_BIT(r, n)   (((r) >> (n)) & 1u)

#define LED_VERMELHO 0
#define LED_VERDE    1
#define LED_AZUL     2
#define BUZZER       7

static void mostrar(const char *acao)
{
    int i;
    printf("%-26s PORTB = ", acao);
    for (i = 7; i >= 0; i--) printf("%u", (unsigned)READ_BIT(PORTB, i));
    printf("  (0x%02X)\n", (unsigned)PORTB);
}

int main(void)
{
    printf("Bit:                                   76543210\n");
    mostrar("estado inicial");
    SET_BIT(PORTB, LED_VERMELHO);   mostrar("SET   bit 0 (vermelho)");
    SET_BIT(PORTB, LED_AZUL);       mostrar("SET   bit 2 (azul)");
    SET_BIT(PORTB, BUZZER);         mostrar("SET   bit 7 (buzzer)");
    CLEAR_BIT(PORTB, LED_AZUL);     mostrar("CLEAR bit 2");
    TOGGLE_BIT(PORTB, LED_VERDE);   mostrar("TOGGLE bit 1");
    TOGGLE_BIT(PORTB, LED_VERDE);   mostrar("TOGGLE bit 1 (de novo)");

    printf("\nMascara: manter so os 4 bits baixos de 0xB6 -> 0x%02X\n", 0xB6u & 0x0Fu);
    printf("Bit 7 do PORTB esta %s\n", READ_BIT(PORTB, BUZZER) ? "ligado" : "desligado");

    PORTB = (uint8_t)((PORTB & 0xF0u) | 0x05u);   /* altera so os 4 bits baixos */
    mostrar("baixos = 0101, altos mantidos");
    return 0;
}

/* EXERCICIOS:
   1) Ligue os 3 LEDs de uma vez com uma unica mascara (0x07).
   2) Escreva uma macro que testa se um bit esta DESLIGADO.
   3) Explique por que usamos ~BIT(n) para limpar e BIT(n) para ligar. */
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c sim_11_bits_registradores */
