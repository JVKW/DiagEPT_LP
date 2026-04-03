#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <string.h>

void limparTela() {
    printf("\033[H\033[J]");
}

float lerNotaValida() {
    float nota;

    do {
        printf("Digite nota (0 a 10): ");
        scanf("%f", &nota);
    } while(nota < 0 || nota > 10);

    return nota;
}

int lerInteiro() {
    char buffer[20];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }
}

float lerFloat() {
    char buffer[20];
    float valor;

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%f", &valor) == 1) {
            return valor;
        }

        printf("Valor inválido. Tente novamente: ");
    }
}

void lerString(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);

    destino[strcspn(destino, "\n")] = '\0';
}

char *ler_arquivo(const char *path)
{
    FILE *f = fopen(path,"r");

    if(!f)
        return NULL;

    fseek(f,0,SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char *buffer = malloc(tamanho + 1);

    fread(buffer,1,tamanho,f);

    buffer[tamanho] = '\0';

    fclose(f);

    return buffer;
}

void escrever_arquivo(const char *path, const char *conteudo)
{
    FILE *f = fopen(path,"w");

    if(!f)
        return;

    fprintf(f,"%s",conteudo);

    fclose(f);
}