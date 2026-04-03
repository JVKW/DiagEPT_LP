#ifndef DOCENTE_MAPPER_H
#define DOCENTE_MAPPER_H

#include "model/docente.h"
#include "cJSON.h"

cJSON *docente_to_json(void *obj);
void *json_to_docente(cJSON *json);

#endif