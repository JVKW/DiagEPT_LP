#include <string.h>

#include "dao/docenteDAO.h"
#include "controller/docente_controller.h"

void cadastrarDocente(Docente *d){

    salvar_docente(d);
}

Docente buscar_docente_id(int id){
    return *buscar_docente(id);
}