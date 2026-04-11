#include "model/estado.h"
#include "include/model/discente.h"

void inicializarEstado(Estado *e) {
    e->totalAlunos = 0;
    e->alunosEvadidos = 0;

    e->somaTeorica = 0;
    e->somaPratica = 0;

    e->maiorNota = 0;
    e->menorNota = 0;

    e->totalAlunos = 0;
}
