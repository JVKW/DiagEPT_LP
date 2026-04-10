#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/turmaDAO.h"
#include "json_mapper/turma_mapper.h"
#include "model/turma.h"

void salvar_turma(Turma *d)
{
    d->id = dao_next_id(TURMA_FILE);
    dao_save(
        TURMA_FILE,
        d,
        turma_to_json
    );
}

Turma *buscar_turma(int id)
{
    return dao_find_by_id(
        TURMA_FILE,
        id,
        json_to_turma
    );
}

void update_turma(Turma *d){
    dao_update(
        TURMA_FILE,
        d->id,
        d,
        turma_to_json
    );
}

void excluir_turma(int id){
    dao_delete_by_id(
        TURMA_FILE,
        id
    );
}

int existe_turma(int id){
    dao_exists(
        TURMA_FILE,
        id
    );
}

void atulizar_turma(Turma *d){
    dao_update(
        TURMA_FILE,
        d->id,
        d,
        turma_to_json
    );
}

DAO_list buscar_turmas(){
    dao_find_all(
        TURMA_FILE,
        json_to_turma
    );
}