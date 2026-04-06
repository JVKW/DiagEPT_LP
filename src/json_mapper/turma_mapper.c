#include <string.h>
#include <stdlib.h>

#include "utils/utils.h"
#include "json_mapper/turma_mapper.h"

cJSON *turma_to_json(void *obj)
{
    Turma *e = (Turma *)obj;

    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json,"id",e->id);
    cJSON_AddStringToObject(json,"codigo",e->codigo);
    cJSON_AddNumberToObject(json,"docente_id",e->docente_id);
    cJSON_AddNumberToObject(json,"qtd_matricula",e->qtd_matricula);

    cJSON_AddItemToObject(
        json,
        "id_matricula",
        int_array_to_json(e->id_matricula, e->qtd_matricula)
    );

    return json;
}

void *json_to_turma(cJSON *json)
{
    Turma *e = malloc(sizeof(Turma));

    e->id = 
        cJSON_GetObjectItem(json, "id")->valueint;
    
    e->docente_id = 
        cJSON_GetObjectItem(json, "docente_id")->valueint;
    
    e->qtd_matricula = 
        cJSON_GetObjectItem(json, "qtd_matricula")->valueint;

    strcpy(e->codigo,
        cJSON_GetObjectItem(json,"codigo")->valuestring);
    
    cJSON *array = cJSON_GetObjectItem(json, "id_matricula");
    e->id_matricula = json_to_int_array(array, &e->qtd_matricula);

    return e;
}