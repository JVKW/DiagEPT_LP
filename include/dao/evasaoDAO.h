#ifndef EVASAODAO_H
#define EVASAODAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/evasao_mapper.h"
#include "model/evasao.h"


#define EVASAO_FILE "data/evasao.json"

void salvar_evasao(Evasao *d);

Evasao *buscar_evasao(int id);

void update_evasao(Evasao *d);

#endif