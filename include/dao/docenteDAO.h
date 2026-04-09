#ifndef DOCENTEDAO_H
#define DOCENTEDAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/docente_mapper.h"
#include "model/docente.h"
#include "model/lista_generica.h"


#define FILE "data/docentes.json"

void salvar_docente(Docente *d);

Docente *buscar_docente(int id);

void update_docente(Docente *d);

DAO_list buscar_docentes();

int existe_docente(int id);

#endif