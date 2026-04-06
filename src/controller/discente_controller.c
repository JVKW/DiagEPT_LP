#include <string.h>

#include "dao/discenteDAO.h"
#include "controller/discente_controller.h"

void cadastrar_discente(char nome[256], int numero_matricula){
    Discente d;
    
    strcpy(d.nome, nome);
    d.numero_matricula = numero_matricula;

    salvar_discente(&d);
}

Discente buscar_discente_id(int id){
    return *buscar_discente(id);
}

void update_discente_id(Discente *d){
    update_discente(d);
}