#ifndef CURSO_MAPPER_H
#define CURSO_MAPPER_H

#include "model/curso.h"
#include "cjson/cJSON.h"

cJSON *curso_to_json(void *obj);
void *json_to_curso(cJSON *json);

#endif