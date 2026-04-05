#ifndef TURMA_MAPPER_H
#define TURMA_MAPPER_H

#include "model/turma.h"
#include "cJSON.h"

cJSON *turma_to_json(void *obj);
void *json_to_turma(cJSON *json);

#endif