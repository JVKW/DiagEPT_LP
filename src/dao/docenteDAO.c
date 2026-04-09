#include "dao/jsonDAO.h"
#include "dao/docenteDAO.h"
#include "json_mapper/docente_mapper.h"
#include "model/lista_generica.h"
#include "model/docente.h"


void salvar_docente(Docente *d)
{
    d->id = dao_next_id(FILE);
    dao_save(
        FILE,
        d,
        docente_to_json
    );
}

Docente *buscar_docente(int id)
{
    return dao_find_by_id(
        FILE,
        id,
        json_to_docente
    );
}

DAO_list buscar_docentes()
{
    return dao_find_all(
        FILE,
        json_to_docente
    );
}

void update_docente(Docente *d){
    dao_update(
        FILE,
        d->id,
        d,
        docente_to_json
    );
}

int existe_docente(int id){
    dao_exists(
        FILE,
        id
    );
}