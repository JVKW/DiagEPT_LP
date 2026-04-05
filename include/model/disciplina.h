#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "model/turma.h"

typedef struct Disciplina
{
    int id;

    char nome[128];
    char codigo[16];
    int carga_horaria_total;
    
    // Sempre que adicionar uma turma na lista
    // atualizar o novo tamanho dela em qtd_turma
    int * id_turma;
    int qtd_turma;
} Disciplina;


#endif