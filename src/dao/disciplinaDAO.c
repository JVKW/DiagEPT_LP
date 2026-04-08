#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/disciplinaDAO.h"
#include "json_mapper/disciplina_mapper.h"
#include "model/disciplina.h"
#include "model/lista_generica.h"

void salvar_disciplina(Disciplina *d)
{
    dao_save(
        DISCIPLINA_FILE,
        d,
        disciplina_to_json
    );
}

Disciplina *buscar_disciplina(int id)
{
    return dao_find_by_id(
        DISCIPLINA_FILE,
        id,
        json_to_disciplina
    );
}

DAO_list buscar_disciplinas()
{
    return dao_find_all(
        DISCIPLINA_FILE,
        json_to_disciplina
    );
}

void update_diciplina(Disciplina *d){
    dao_update(
        DISCIPLINA_FILE,
        d->id,
        d,
        disciplina_to_json
    );
}

void excluir_disciplina(int id){
    dao_delete_by_id(
        DISCIPLINA_FILE,
        id
    );
}

int existe_disciplina(int id){
    return dao_exists(
        DISCIPLINA_FILE,
        id
    );
}