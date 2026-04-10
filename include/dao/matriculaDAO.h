#ifndef MATRICULADAO_H
#define MATRICULADAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/matricula_mapper.h"
#include "model/matricula.h"
#include "model/lista_generica.h"


#define MATRICULA_FILE "data/matricula.json"

void salvar_matricula(Matricula *d);

Matricula *buscar_matricula(int id);

void update_matricula(Matricula *d);

DAO_list buscar_matriculas();

int existe_matricula(int id);

void excluir_matricula(int id);

#endif