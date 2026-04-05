#ifndef DISCENTE_MAPPER_H
#define DISCENTE_MAPPER_H

#include "model/discente.h"
#include "cJSON.h"

cJSON *discente_to_json(void *obj);
void *json_to_discente(cJSON *json);

#endif