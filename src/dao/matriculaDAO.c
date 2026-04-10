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

void update_matricula(Matricula *m) {
    dao_delete_by_id(FILE, m->id);  // Remove o registro antigo
    dao_save(FILE, m, matricula_to_json);  // Salva o atualizado (adiciona ao array)
}

Matricula *buscar_matricula(int id)
{
    return dao_find_by_id(
        FILE,
        id,
        json_to_matricula
    );
}