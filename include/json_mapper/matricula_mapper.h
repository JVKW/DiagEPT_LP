#ifndef MATRICULA_MAPPER_H
#define MATRICULA_MAPPER_H

#include "model/matricula.h"
#include "cJSON.h"

cJSON *matricula_to_json(void *obj);
void *json_to_matricula(cJSON *json);

#endif