#ifndef MATRICULADAO_H
#define MATRICULADAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/matricula_mapper.h"
#include "model/matricula.h"


#define FILE "data/matricula.json"

void salvar_matricula(Matricula *d);

void update_matricula(Matricula *m);

Matricula *buscar_matricula(int id);

#endif