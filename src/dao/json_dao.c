#include "dao/jsonDAO.h"
#include "utils/utils.h"
#include "model/lista_generica.h"

#include <stdlib.h>
#include <string.h>


void dao_save(const char *file, void *obj, to_json_fn to_json)
{
    char *conteudo = ler_arquivo(file);

    cJSON *array;

    if(conteudo)
        array = cJSON_Parse(conteudo);
    else
        array = cJSON_CreateArray();

    cJSON *json_obj = to_json(obj);

    cJSON_AddItemToArray(array,json_obj);

    char *saida = cJSON_Print(array);

    escrever_arquivo(file,saida);

    free(saida);
    free(conteudo);

    cJSON_Delete(array);
}

void dao_update(const char *file, int id, void *obj, to_json_fn to_json)
{
    char *conteudo = ler_arquivo(file);

    if (!conteudo)
        return;

    cJSON *array = cJSON_Parse(conteudo);
    if (!array)
    {
        free(conteudo);
        return;
    }

    cJSON *item = NULL;

    cJSON_ArrayForEach(item, array)
    {
        cJSON *json_id = cJSON_GetObjectItem(item, "id");

        if (cJSON_IsNumber(json_id) && json_id->valueint == id)
        {
            cJSON *novo = to_json(obj);
            cJSON_ReplaceItemViaPointer(array, item, novo);
            break;
        }
    }

    char *saida = cJSON_Print(array);

    escrever_arquivo(file, saida);

    free(saida);
    free(conteudo);
    cJSON_Delete(array);
}

int dao_delete_by_id(const char *file, int id)
{
    char *conteudo = ler_arquivo(file);

    if (!conteudo)
        return 0;

    cJSON *array = cJSON_Parse(conteudo);

    if (!array)
    {
        free(conteudo);
        return 0;
    }

    int size = cJSON_GetArraySize(array);

    for (int i = 0; i < size; i++)
    {
        cJSON *item = cJSON_GetArrayItem(array, i);

        cJSON *json_id = cJSON_GetObjectItem(item, "id");

        if (json_id && json_id->valueint == id)
        {
            cJSON_DeleteItemFromArray(array, i);

            char *saida = cJSON_Print(array);

            escrever_arquivo(file, saida);

            free(saida);
            free(conteudo);

            cJSON_Delete(array);

            return 1;
        }
    }

    cJSON_Delete(array);
    free(conteudo);

    return 0;
}

int dao_next_id(const char *file)
{
    char *conteudo = ler_arquivo(file);

    if (!conteudo)
        return 1; // primeiro registro

    cJSON *array = cJSON_Parse(conteudo);

    if (!array)
    {
        free(conteudo);
        return 1;
    }

    int size = cJSON_GetArraySize(array);
    int maior = 0;

    for (int i = 0; i < size; i++)
    {
        cJSON *item = cJSON_GetArrayItem(array, i);
        cJSON *json_id = cJSON_GetObjectItem(item, "id");

        if (json_id && json_id->valueint > maior)
        {
            maior = json_id->valueint;
        }
    }

    cJSON_Delete(array);
    free(conteudo);

    return maior + 1;
}

void *dao_find_by_id(
    const char *file,
    int id,
    from_json_fn from_json)
{
    char *conteudo = ler_arquivo(file);

    if(!conteudo)
        return NULL;

    cJSON *array = cJSON_Parse(conteudo);

    int size = cJSON_GetArraySize(array);

    for(int i=0;i<size;i++)
    {
        cJSON *item = cJSON_GetArrayItem(array,i);

        int json_id =
            cJSON_GetObjectItem(item,"id")->valueint;

        if(json_id == id)
        {
            void *obj = from_json(item);

            cJSON_Delete(array);
            free(conteudo);

            return obj;
        }
    }

    cJSON_Delete(array);
    free(conteudo);

    return NULL;
}

DAO_list dao_find_all(
    const char *file,
    from_json_fn from_json)
{
    DAO_list result;
    result.items = NULL;
    result.size = 0;

    char *conteudo = ler_arquivo(file);

    if(!conteudo)
        return result;

    cJSON *array = cJSON_Parse(conteudo);

    if(!array)
    {
        free(conteudo);
        return result;
    }

    int size = cJSON_GetArraySize(array);

    result.items = malloc(sizeof(void*) * size);
    result.size = size;

    for(int i = 0; i < size; i++)
    {
        cJSON *item = cJSON_GetArrayItem(array, i);
        result.items[i] = from_json(item);
    }

    cJSON_Delete(array);
    free(conteudo);

    return result;
}