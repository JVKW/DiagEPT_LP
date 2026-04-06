#include <string.h>

#include "dao/discenteDAO.h"
#include "controller/discente_controller.h"

void cadastrarDiscente(char nome[256], int numero_matricula){
    Discente d;
    
    strcpy(d.nome, nome);
    d.numero_matricula = numero_matricula;

    salvar_discente(&d);
}

Discente buscarDiscentePorId(int id){
    return *buscar_discente(id);
}