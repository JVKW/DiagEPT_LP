#include <string.h>

#include "dao/discenteDAO.h"
#include "controller/discente_controller.h"

void cadastrar_discente(Discente *d){
    salvar_discente(d);
}

Discente buscar_discente_id(int id){
    return *buscar_discente(id);
}

void update_discente_id(Discente *d){
    update_discente(d);
}