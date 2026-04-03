#ifndef DISCENTEDAO_H
#define DISCENTEDAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/discente_mapper.h"
#include "model/discente.h"


#define DOCENTE_FILE "data/discentes.json"

void salvar_discente(Discente *d);

Discente *buscar_discente(int id);

#endif