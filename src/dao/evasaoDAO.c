#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/evasaoDAO.h"
#include "json_mapper/evasao_mapper.h"
#include "model/evasao.h"

void salvar_evasao(Evasao *d)
{
    d->id = dao_next_id(EVASAO_FILE);
    dao_save(
        EVASAO_FILE,
        d,
        evasao_to_json
    );
}

Evasao *buscar_evasao(int id)
{
    return dao_find_by_id(
        EVASAO_FILE,
        id,
        json_to_evasao
    );
}

void update_evasao(Evasao *d){
    dao_update(
        EVASAO_FILE,
        d->id,
        d,
        evasao_to_json
    );
}