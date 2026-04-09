
#ifndef TURMA_H
#define TURMA_H

#include "model/matricula.h"

typedef struct Turma
{
    int id;
    char codigo[8];
    int docente_id;
    int id_disciplina;

    int *id_matricula;
    int qtd_matricula;
} Turma;



#endif