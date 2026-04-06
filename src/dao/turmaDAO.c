#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/turmaDAO.h"
#include "json_mapper/turma_mapper.h"
#include "model/turma.h"

void salvar_turma(Turma *d)
{
    if (d->id == NULL)
        d->id = dao_next_id(FILE);
    dao_save(
        FILE,
        d,
        turma_to_json
    );
}

Turma *buscar_turma(int id)
{
    return dao_find_by_id(
        FILE,
        id,
        json_to_turma
    );
}