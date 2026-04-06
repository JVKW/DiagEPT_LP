#include "dao/jsonDAO.h"
#include "dao/docenteDAO.h"
#include "json_mapper/docente_mapper.h"
#include "model/docente.h"


#define DOCENTE_FILE "data/docentes.json"

void salvar_docente(Docente *d)
{
    if (d->id == NULL)
        d->id = dao_next_id(FILE);
    dao_save(
        DOCENTE_FILE,
        d,
        docente_to_json
    );
}

Docente *buscar_docente(int id)
{
    return dao_find_by_id(
        DOCENTE_FILE,
        id,
        json_to_docente
    );
}