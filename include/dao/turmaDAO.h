#ifndef TURMADAO_H
#define TURMADAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/turma_mapper.h"
#include "model/turma.h"


#define TURMA_FILE "data/turma.json"

void salvar_turma(Turma *d);

Turma *buscar_turma(int id);

void update_turma(Turma *d);

int existe_turma(int id);

void excluir_turma(int id);

#endif