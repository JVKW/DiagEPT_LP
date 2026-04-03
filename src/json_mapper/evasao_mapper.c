#include "json_mapper/evasao_mapper.h"
#include <string.h>
#include <stdlib.h>

cJSON *evasao_to_json(void *obj)
{
    Evasao *e = (Evasao *)obj;

    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json,"id",e->id);
    cJSON_AddStringToObject(json,"motivo",e->motivo);
    

    return json;
}

void *json_to_evasao(cJSON *json)
{
    Evasao *e = malloc(sizeof(Evasao));

    e->id = 
        cJSON_GetObjectItem(json, "id")->valueint;
    strcpy(e->motivo,
        cJSON_GetObjectItem(json,"motivo")->valuestring);

    return e;
}