#include <string.h>
#include <stdlib.h>

#include "utils/utils.h"
#include "json_mapper/disciplina_mapper.h"

cJSON *disciplina_to_json(void *obj)
{
    Disciplina *e = (Disciplina *)obj;

    cJSON *json = cJSON_CreateObject();

    
    cJSON_AddNumberToObject(json,"id",e->id);
    
    cJSON_AddStringToObject(json,"nome",e->nome);
    
    cJSON_AddStringToObject(json,"codigo",e->codigo);
    
    cJSON_AddNumberToObject(json,"carga_horaria_total",e->carga_horaria_total);
    
    cJSON_AddNumberToObject(json,"qtd_turma",e->qtd_turma);
    
    cJSON_AddItemToObject(
        json,
        "id_turma",
        int_array_to_json(e->id_turma, e->qtd_turma)
    );

    return json;
}

void *json_to_disciplina(cJSON *json)
{
    Disciplina *e = malloc(sizeof(Disciplina));

    e->id = 
        cJSON_GetObjectItem(json, "id")->valueint;

    strcpy(e->nome,
        cJSON_GetObjectItem(json,"nome")->valuestring);

    strcpy(e->codigo,
        cJSON_GetObjectItem(json,"codigo")->valuestring);

    e->carga_horaria_total = 
        cJSON_GetObjectItem(json, "carga_horaria_total")->valueint;
    
    e->qtd_turma = 
        cJSON_GetObjectItem(json, "qtd_turma")->valueint;

    cJSON *array = cJSON_GetObjectItem(json, "id_turma");

    e->id_turma = json_to_int_array(array, &e->qtd_turma);

    return e;
}