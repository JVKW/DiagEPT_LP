#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/cursoDAO.h"
#include "json_mapper/curso_mapper.h"
#include "model/curso.h"

void salvar_curso(Curso *d)
{
    d->id = dao_next_id(CURSO_FILE);
    dao_save(
        CURSO_FILE,
        d,
        curso_to_json
    );
}

Curso *buscar_curso(int id)
{
    return dao_find_by_id(
        CURSO_FILE,
        id,
        json_to_curso
    );
}

DAO_list buscar_cursos( ){
    return dao_find_all(
        CURSO_FILE,
        json_to_curso
    );
}

void update_curso(Curso *d){
    dao_update(
        CURSO_FILE,
        d->id,
        d,
        curso_to_json
    );
}

void excluir_curso(int id){
    dao_delete_by_id(
        CURSO_FILE,
        id
    );
}

int existe_curso(int id){
    return dao_exists(
        CURSO_FILE,
        id
    );
}

void atualizar_curso(Curso *d){
    dao_update(
        CURSO_FILE,
        d->id,
        d,
        curso_to_json
    );
}