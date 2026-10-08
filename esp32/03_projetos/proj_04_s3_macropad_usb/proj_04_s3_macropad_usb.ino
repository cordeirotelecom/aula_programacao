/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  PROJETO 4 - Macropad USB (SOMENTE ESP32-S3)

  OBJETIVO
    Transformar o ESP32-S3 em um teclado USB com 3 botoes de atalho:
    Copiar (Ctrl+C), Colar (Ctrl+V) e Mostrar area de trabalho (Win+D).

  MATERIAIS
    ESP32-S3 com USB nativo, 3 botoes, jumpers, protoboard.
    O ESP32 classico NAO serve: ele nao tem USB nativo.

  LIGACAO
    Botao 1 entre GPIO 4 e GND (Copiar)
    Botao 2 entre GPIO 5 e GND (Colar)
    Botao 3 entre GPIO 6 e GND (Mostrar area de trabalho)

  CONFIGURACAO NA ARDUINO IDE (Ferramentas)
    Placa: ESP32S3 Dev Module
    USB Mode: "USB-OTG (TinyUSB)"  (ou "Hardware CDC and JTAG" so para carregar)
    USB CDC On Boot: Disabled (se o Monitor Serial nao for necessario)
    Para carregar: use a porta COM da placa. Se nao aparecer, segure BOOT,
    aperte RESET, solte BOOT (modo de gravacao) e depois escolha a porta.
    Conecte o cabo na porta USB marcada "USB" (nativa), nao na "UART".

  COMO TESTAR
    Depois de carregar, o PC reconhece um novo teclado. Abra o Bloco de Notas,
    escreva um texto, selecione e use os botoes.
*/
#if !CONFIG_IDF_TARGET_ESP32S3
#error "Este projeto so funciona no ESP32-S3: escolha a placa ESP32S3 Dev Module."
#endif

#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Teclado;

const int PINO_COPIAR = 4;
const int PINO_COLAR = 5;
const int PINO_AREA = 6;

void atalho(uint8_t modificador, char tecla) {
  Teclado.press(modificador);  // segura Ctrl ou Win
  Teclado.press(tecla);
  delay(50);
  Teclado.releaseAll();        // solta tudo
}

void setup() {
  pinMode(PINO_COPIAR, INPUT_PULLUP);
  pinMode(PINO_COLAR, INPUT_PULLUP);
  pinMode(PINO_AREA, INPUT_PULLUP);
  Teclado.begin();
  USB.begin();
  delay(1000);  // da tempo do PC reconhecer o teclado
}

void loop() {
  if (digitalRead(PINO_COPIAR) == LOW) {
    atalho(KEY_LEFT_CTRL, 'c');
    delay(300);  // evita repetir sem querer
  }
  if (digitalRead(PINO_COLAR) == LOW) {
    atalho(KEY_LEFT_CTRL, 'v');
    delay(300);
  }
  if (digitalRead(PINO_AREA) == LOW) {
    atalho(KEY_LEFT_GUI, 'd');
    delay(300);
  }
}

/*
  EXERCICIOS
  1) Troque um botao para digitar um texto com Teclado.print("Ola!").
  2) Crie o atalho Ctrl+Z (desfazer).
  3) Adicione um quarto botao para Alt+Tab (KEY_LEFT_ALT e KEY_TAB).
  4) Pesquise: o que significa HID?
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
