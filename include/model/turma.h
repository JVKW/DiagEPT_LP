
#ifndef TURMA_H
#define TURMA_H

#include "model/docente.h"
#include "model/matricula.h"

typedef struct Turma
{
    int id;
    char periodo[64];

    Docente docente;
    Matricula *matriculas;
    int matriculas_count;
} Turma;



#endif