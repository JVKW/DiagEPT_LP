#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/matriculaDAO.h"
#include "json_mapper/matricula_mapper.h"
#include "model/matricula.h"

void salvar_matricula(Matricula *d)
{
    d->id = dao_next_id(FILE);
    dao_save(
        FILE,
        d,
        matricula_to_json
    );
}

Matricula *buscar_matricula(int id)
{
    return dao_find_by_id(
        FILE,
        id,
        json_to_matricula
    );
}

void update_matricula(Matricula *d){
    dao_update(
        FILE,
        d->id,
        d,
        matricula_to_json
    );
}