#ifndef DISCIPLINA_MAPPER_H
#define DISCIPLINA_MAPPER_H

#include "model/disciplina.h"
#include "cjson/cJSON.h"

cJSON *disciplina_to_json(void *obj);
void *json_to_disciplina(cJSON *json);

#endif