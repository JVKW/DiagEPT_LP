#include "json_mapper/matricula_mapper.h"
#include <string.h>
#include <stdlib.h>

cJSON *matricula_to_json(void *obj)
{
    Matricula *d = (Matricula *)obj;

    cJSON *json = cJSON_CreateObject();
    
    cJSON_AddNumberToObject(json,"id", d->id);
    cJSON_AddNumberToObject(json, "nota_pratica", d->nota_pratica);
    cJSON_AddNumberToObject(json, "nota_teorica", d->nota_teorica);
    cJSON_AddNumberToObject(json, "tempo_ausente", d->tempo_ausente);
    cJSON_AddNumberToObject(json, "aulas_ausente", d->aulas_ausente);
    cJSON_AddBoolToObject(json, "tem_evasao", d->tem_evasao);
    cJSON_AddStringToObject(json, "status", d->status);
    cJSON_AddNumberToObject(json, "discente_id", d->discente_id);
    cJSON_AddNumberToObject(json, "id_evasao", d->id_evasao);

    return json;
}

void *json_to_matricula(cJSON *json)
{
    Matricula *d = malloc(sizeof(Matricula));

    d->id =
        cJSON_GetObjectItem(json,"id")->valueint;
    d->nota_pratica = 
        cJSON_GetObjectItem(json,"nota_pratica")->valueint;    
    d->nota_teorica = 
        cJSON_GetObjectItem(json,"nota_teorica")->valueint;    
    d->tempo_ausente = 
        cJSON_GetObjectItem(json,"tempo_ausente")->valueint;    
    d->aulas_ausente = 
        cJSON_GetObjectItem(json,"aulas_ausente")->valueint;    
    d->tem_evasao =
        cJSON_IsTrue(cJSON_GetObjectItem(json, "tem_evasao"));
    strcpy(d->status,
        cJSON_GetObjectItem(json,"status")->valuestring);
    d->discente_id = 
        cJSON_GetObjectItem(json,"discente_id")->valueint;
    d->id_evasao = 
        cJSON_GetObjectItem(json,"id_evasao")->valueint;
    
    return d;
}