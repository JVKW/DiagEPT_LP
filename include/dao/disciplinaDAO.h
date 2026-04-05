#ifndef DISCIPLINADAO_H
#define DISCIPLINADAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/disciplina_mapper.h"
#include "model/disciplina.h"


#define FILE "data/disciplina.json"

void salvar_disciplina(Disciplina *d);

Disciplina *buscar_disciplina(int id);

#endif