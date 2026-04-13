#include <string.h>
#include <stdio.h>

#include "dao/docenteDAO.h"
#include "controller/docente_controller.h"

int cadastrar_docente(Docente *d){

    DAO_list docentes =  buscar_docentes();
    
    int n = docentes.size;
    for (int i = 0; i < n; i++){
        Docente * temp = docentes.items[i];
         
        if(strcmp(temp->login, d->login) == 0) {
            puts("Erro ao salvar docente:\nO login informado já está em uso!");
            return -1;
        }
    }
    salvar_docente(d);
    return 0;
}

int logar_docente(char * login, char * senha){
    DAO_list docentes =  buscar_docentes();
    
    int n = docentes.size;
    for (int i = 0; i < n; i++){
        Docente * temp = docentes.items[i];
         
        if( strcmp(temp->login, login) == 0 &&
            strcmp(temp->senha, senha) == 0   ) {
            return temp->id;
        }
    }
    
    puts("Erro ao logar docente:\nLogin ou senha incorretos!");
    return -1;
}


Docente buscar_docente_id(int id){
    return *buscar_docente(id);
}
