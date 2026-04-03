#ifndef MATRICULA_H
#define MATRICULA_H

#include <stdbool.h>
#include "model/discente.h"
#include "model/evasao.h"

typedef struct Matricula
{
    int id;
    float nota_teorica;
    float nota_pratica;
    int tempo_ausente;
    int aulas_ausente;
    bool tem_evasao;
    char status[128];

    int discente_id;
    int id_evasao;
    
} Matricula;


#endif