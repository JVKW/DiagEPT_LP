#include "json_mapper/docente_mapper.h"
#include <string.h>
#include <stdlib.h>

cJSON *docente_to_json(void *obj)
{
    Docente *d = (Docente *)obj;

    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json,"id",d->id);
    cJSON_AddStringToObject(json,"nome",d->nome);
    cJSON_AddStringToObject(json,"login",d->login);
    cJSON_AddStringToObject(json,"senha",d->senha);

    return json;
}

void *json_to_docente(cJSON *json)
{
    Docente *d = malloc(sizeof(Docente));

    d->id =
        cJSON_GetObjectItem(json,"id")->valueint;

    strcpy(d->nome,
        cJSON_GetObjectItem(json,"nome")->valuestring);

    strcpy(d->login,
        cJSON_GetObjectItem(json,"login")->valuestring);

    strcpy(d->senha,
        cJSON_GetObjectItem(json,"senha")->valuestring);

    return d;
}