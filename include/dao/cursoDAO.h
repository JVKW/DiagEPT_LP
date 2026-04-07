#ifndef CURSODAO_H
#define CURSODAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/curso_mapper.h"
#include "model/curso.h"


#define FILE "data/curso.json"

void salvar_curso(Curso *d);

Curso *buscar_curso(int id);

void update_curso(Curso *d);

#endif