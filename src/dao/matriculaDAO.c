#include <stdio.h>

#include "dao/jsonDAO.h"
#include "dao/matriculaDAO.h"
#include "json_mapper/matricula_mapper.h"
#include "model/matricula.h"
#include "model/lista_generica.h"

void salvar_matricula(Matricula *d)
{
    dao_save(
        MATRICULA_FILE,
        d,
        matricula_to_json
    );
}

Matricula *buscar_matricula(int id)
{
    return dao_find_by_id(
        MATRICULA_FILE,
        id,
        json_to_matricula
    );
}

DAO_list buscar_matriculas()
{
    return dao_find_all(
        MATRICULA_FILE,
        json_to_matricula
    );
}

void update_matricula(Matricula *d){
    dao_update(
        MATRICULA_FILE,
        d->id,
        d,
        matricula_to_json
    );
}

int existe_matricula(int id){
    dao_exists(
        MATRICULA_FILE,
        id
    );
}

void excluir_matricula(int id){
    dao_delete_by_id(
        MATRICULA_FILE,
        id
    );
}