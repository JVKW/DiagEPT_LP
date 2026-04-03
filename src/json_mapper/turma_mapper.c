#include "json_mapper/turma_mapper.h"
#include <string.h>
#include <stdlib.h>

cJSON *turma_to_json(void *obj)
{
    Turma *e = (Turma *)obj;

    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json,"id",e->id);
    cJSON_AddStringToObject(json,"codigo",e->codigo);
    

    return json;
}

void *json_to_turma(cJSON *json)
{
    Turma *e = malloc(sizeof(Turma));

    e->id = 
        cJSON_GetObjectItem(json, "id")->valueint;
    strcpy(e->codigo,
        cJSON_GetObjectItem(json,"codigo")->valuestring);

    return e;
}