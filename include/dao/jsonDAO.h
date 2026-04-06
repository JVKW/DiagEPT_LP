#ifndef JSON_DAO_H
#define JSON_DAO_H

#include "cjson/cJSON.h"


typedef cJSON *(*to_json_fn)(void *obj);
typedef void *(*from_json_fn)(cJSON *json);

void dao_save(const char *file,
    void *obj,
    to_json_fn to_json
);

void dao_update(const char *file,
    int id,
    void *obj,
    to_json_fn to_json
);

void *dao_find_by_id(
    const char *file,
    int id,
    from_json_fn from_json
);

int dao_delete_by_id(
    const char *file,
    int id
);

int dao_next_id(
    const char *file
);

#endif