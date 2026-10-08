/* Elaborado pelo Prof. Vagner Cordeiro */
#include <stdio.h>

/* AULA - Arquivos
   fopen abre, fprintf escreve, fgets le linha, fclose fecha.
   Modos: "w" escrever (apaga o conteudo), "r" ler, "a" acrescentar. */
int main(void)
{
    const char *nome_arquivo = "dados_teste.txt";
    char linha[80];

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Nao foi possivel criar o arquivo.\n");
        return 1;
    }
    fprintf(arquivo, "Temperatura: 24\n");
    fprintf(arquivo, "Umidade: 60\n");
    fclose(arquivo);

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("Lido: %s", linha);
    }
    fclose(arquivo);

    remove(nome_arquivo);            /* apaga o arquivo de teste */
    return 0;
}

/* EXERCICIOS:
   1. Escreva uma terceira linha: "Pressao: 1013".
   2. Comente a linha remove(...) e abra o arquivo criado no Bloco de Notas.
*/
/* Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\executar.ps1" c 09_arquivos */
