#include <stdio.h>
#include "controller/evasao.h"
#include "utils/utils.h"

void registrarEvasao(Estado *e) {
    char motivo[300];

    printf("Motivo da Evasao: ");
    lerString(motivo, 300);

    e->alunosEvadidos++;

    printf("Evasao Registrada: %s\n", motivo);
    
}