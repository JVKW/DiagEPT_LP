#include "json_mapper/discente_mapper.h"
#include <string.h>
#include <stdlib.h>

cJSON *discente_to_json(void *obj)
{
    Discente *d = (Discente *)obj;

    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json,"id",d->id);
    cJSON_AddStringToObject(json,"nome",d->nome);
    cJSON_AddNumberToObject(json,"numero_matricula",d->numero_matricula);
    

    return json;
}

void *json_to_discente(cJSON *json)
{
    Discente *d = malloc(sizeof(Discente));

    d->id =
        cJSON_GetObjectItem(json,"id")->valueint;

    strcpy(d->nome,
        cJSON_GetObjectItem(json,"nome")->valuestring);

    d->numero_matricula =
    cJSON_GetObjectItem(json,"numero_matricula")->valueint;

    return d;
}