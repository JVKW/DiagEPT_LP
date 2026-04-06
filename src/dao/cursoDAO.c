#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/cursoDAO.h"
#include "json_mapper/curso_mapper.h"
#include "model/curso.h"

void salvar_curso(Curso *d)
{
    if (d->id == 0)
        d->id = dao_next_id(FILE);
    dao_save(
        FILE,
        d,
        curso_to_json
    );
}

Curso *buscar_curso(int id)
{
    return dao_find_by_id(
        FILE,
        id,
        json_to_curso
    );
}

void update_curso(Curso *d){
    dao_update(
        FILE,
        d->id,
        d,
        curso_to_json
    );
}