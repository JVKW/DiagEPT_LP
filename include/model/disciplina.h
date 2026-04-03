#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "model/turma.h"

typedef struct Disciplina
{
    int id;

    char nome[128];
    char codigo[16];
    int carga_horaria_total;
    
    Turma *turmas;
    int turmas_count;
} Disciplina;


#endif