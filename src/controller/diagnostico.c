#include <stdio.h>
#include "controller/diagnostico.h"
#include "model/estado.h"
#include "view/menu.h"

void mostrarDiagnostico(Estado *e) {
    if (e->totalAlunos == 0) {
        printf("Nenhum dado armazenado.");
        return;
    }

    float mediaT = e->somaTeorica / e->totalAlunos;
    float mediaP = e->somaPratica / e->totalAlunos;
    float mediaGeral = (mediaT + mediaP) / 2;

    printf(
        "Alunos: %d\n"
        "Media Teorica: %.2f\n"
        "Media Pratica: %.2f\n"
        "Media Geral: %.2f\n"
        "Maior Nota: %.2f\n"
        "Menor Nota: %.2f\n",
        e->totalAlunos,
        mediaT,
        mediaP,
        mediaGeral,
        e->maiorNota,
        e->menorNota
    );

    if (mediaGeral >= 7) {
        printf("Situacao: Turma destaque\n");
    } else {
        printf("Situacao: Turma com problemas.");
    }
}