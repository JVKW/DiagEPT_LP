#include <string.h>
#include <stdlib.h>

#include "utils/utils.h"
#include "json_mapper/curso_mapper.h"

cJSON *curso_to_json(void *obj)
{
    Curso *e = (Curso *)obj;

    cJSON *json = cJSON_CreateObject();

    
    cJSON_AddNumberToObject(json,"id",e->id);
    
    cJSON_AddStringToObject(json,"nome",e->nome);
    
    cJSON_AddStringToObject(json,"codigo",e->codigo);
    
    cJSON_AddNumberToObject(json,"carga_horaria_total",e->carga_horaria_total);
    
    cJSON_AddNumberToObject(json,"qtd_disciplinas",e->qtd_disciplinas);
    
    cJSON_AddItemToObject(
        json,
        "id_disciplinas",
        int_array_to_json(e->id_disciplinas, e->qtd_disciplinas)
    );

    return json;
}

void *json_to_curso(cJSON *json)
{
    Curso *e = malloc(sizeof(Curso));

    e->id = 
        cJSON_GetObjectItem(json, "id")->valueint;

    strcpy(e->nome,
        cJSON_GetObjectItem(json,"nome")->valuestring);

    strcpy(e->codigo,
        cJSON_GetObjectItem(json,"codigo")->valuestring);

    e->carga_horaria_total = 
        cJSON_GetObjectItem(json, "carga_horaria_total")->valueint;
    
    e->qtd_disciplinas = 
        cJSON_GetObjectItem(json, "qtd_disciplinas")->valueint;

    cJSON *array = cJSON_GetObjectItem(json, "id_disciplinas");

    e->id_disciplinas = json_to_int_array(array, &e->qtd_disciplinas);

    return e;
}