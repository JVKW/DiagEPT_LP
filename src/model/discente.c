#include <stdio.h>
#include <stdlib.h>
#include "model/discente.h"
#include "utils/utils.h"

Discente *pede_captura_discente() {
    Discente *novo = malloc(sizeof(Discente));
    if (!novo) {
        return NULL;
    }

    printf("\nDigite o nome do aluno: ");
    lerString(novo->nome, 256);

    printf("\nDigite o número de matrícula do aluno: ");
    novo->numero_matricula = lerInteiro();

    return novo;
}
