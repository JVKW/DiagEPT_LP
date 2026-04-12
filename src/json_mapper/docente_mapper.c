#include "json_mapper/docente_mapper.h"
#include <string.h>
#include <stdlib.h>

cJSON *docente_to_json(void *obj)
{
    Docente *d = (Docente *)obj;

    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json, "id", d->id);
    cJSON_AddStringToObject(json, "nome", d->nome);
    cJSON_AddStringToObject(json, "login", d->login);
    cJSON_AddStringToObject(json, "senha", d->senha);

    return json;
}

void *json_to_docente(cJSON *json)
{
    Docente *d = malloc(sizeof(Docente));

    if (!d) return NULL;

    memset(d, 0, sizeof(Docente));

    cJSON *id = cJSON_GetObjectItem(json, "id");
    if (cJSON_IsNumber(id))
        d->id = id->valueint;

    cJSON *nome = cJSON_GetObjectItem(json, "nome");
    if (cJSON_IsString(nome) && nome->valuestring) {
        strncpy(d->nome, nome->valuestring, sizeof(d->nome) - 1);
        d->nome[sizeof(d->nome) - 1] = '\0';
    }

    cJSON *login = cJSON_GetObjectItem(json, "login");
    if (cJSON_IsString(login) && login->valuestring) {
        strncpy(d->login, login->valuestring, sizeof(d->login) - 1);
        d->login[sizeof(d->login) - 1] = '\0';
    }

    cJSON *senha = cJSON_GetObjectItem(json, "senha");
    if (cJSON_IsString(senha) && senha->valuestring) {
        strncpy(d->senha, senha->valuestring, sizeof(d->senha) - 1);
        d->senha[sizeof(d->senha) - 1] = '\0';
    }

    return d;
}