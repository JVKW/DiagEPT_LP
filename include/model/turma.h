
#ifndef TURMA_H
#define TURMA_H

#include "model/matricula.h"

typedef struct Turma
{
    int id;
    char periodo[64];
    int docente_id;

    int *id_matricula;
    int matriculas_count;
} Turma;



#endif