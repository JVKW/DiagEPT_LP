#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/discenteDAO.h"
#include "json_mapper/discente_mapper.h"
#include "model/discente.h"


#define DISCENTE_FILE "data/discentes.json"

void salvar_discente(Discente *d)
{
    d->id = dao_next_id(DISCENTE_FILE);
    dao_save(
        DISCENTE_FILE,
        d,
        discente_to_json
    );
}

Discente *buscar_discente(int id)
{
    return dao_find_by_id(
        DISCENTE_FILE,
        id,
        json_to_discente
    );
}