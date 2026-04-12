#ifndef DOCENTE_MAPPER_H
#define DOCENTE_MAPPER_H

#include "model/docente.h"
#include "cjson/cJSON.h"

cJSON *docente_to_json(void *obj);
void *json_to_docente(cJSON *json);
void *json_to_docentes(cJSON *json, int size);

#endif