#ifndef EVASAODAO_H
#define EVASAODAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/evasao_mapper.h"
#include "model/evasao.h"


#define FILE "data/evasao.json"

void salvar_evasao(Evasao *d);

Evasao *buscar_evasao(int id);

#endif