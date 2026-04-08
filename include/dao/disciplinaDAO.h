#ifndef DISCIPLINADAO_H
#define DISCIPLINADAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/disciplina_mapper.h"
#include "model/disciplina.h"
#include "model/lista_generica.h"


#define DISCIPLINA_FILE "data/disciplina.json"

void salvar_disciplina(Disciplina *d);

Disciplina *buscar_disciplina(int id);

void update_disciplina(Disciplina *d);

DAO_list buscar_disciplinas();

int existe_disciplina(int id);

void excluir_disciplina(int id);

#endif