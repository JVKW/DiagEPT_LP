#ifndef EVASAO_MAPPER_H
#define EVASAO_MAPPER_H

#include "model/evasao.h"
#include "cJSON.h"

cJSON *evasao_to_json(void *obj);
void *json_to_evasao(cJSON *json);

#endif