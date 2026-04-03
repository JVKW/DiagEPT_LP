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