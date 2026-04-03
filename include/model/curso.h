#ifndef CURSO_H
#define CURSO_H

#include "model/disciplina.h"

typedef struct Curso
{
    int id;

    char nome[128];
    char codigo[16];
    int carga_horaria_total;
    
    int * id_disciplinas;
    int qtd_disciplinas;
} Curso;


#endif