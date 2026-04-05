#include <string.h>

#include "dao/docenteDAO.h"
#include "controller/docente_controller.h"

void cadastrarDocente(char nome[256], char login[256], char senha[128]){
    Docente d;
    
    strcpy(d.nome, nome);
    strcpy(d.login, login);
    strcpy(d.senha, senha);

    salvar_docente(&d);
}

Docente buscarDocentePorId(int id){
    return *buscar_docente(id);
}