#ifndef DOCENTEDAO_H
#define DOCENTEDAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/docente_mapper.h"
#include "model/docente.h"


#define FILE "data/docentes.json"

void salvar_docente(Docente *d);

Docente *buscar_docente(int id);

#endif