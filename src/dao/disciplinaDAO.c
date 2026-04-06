#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/disciplinaDAO.h"
#include "json_mapper/disciplina_mapper.h"
#include "model/disciplina.h"

void salvar_disciplina(Disciplina *d)
{
    if (d->id == 0)
        d->id = dao_next_id(FILE);
    dao_save(
        FILE,
        d,
        disciplina_to_json
    );
}

Disciplina *buscar_disciplina(int id)
{
    return dao_find_by_id(
        FILE,
        id,
        json_to_disciplina
    );
}

void update_diciplina(Disciplina *d){
    dao_update(
        FILE,
        d->id,
        d,
        disciplina_to_json
    );
}