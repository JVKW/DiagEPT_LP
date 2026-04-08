#include <string.h>
#include <stdio.h>

#include "controller/curso_controller.h"
#include "dao/cursoDAO.h"
#include "utils/utils.h"

/*
    CÓDIGOS DE RETORNO:
     0 SUCESSO
    -1 ERRO INFORMAÇÕES INCORRETAS
    -2 ERRO AO REALIZAR A OPERAÇÃO

*/
int cadastrar_curso(Curso *c){
    
    c->qtd_disciplinas == 0;
    strcpy(c->codigo, removerEspacos(c->codigo));


    char * temp = removerEspacos(c->nome);

    if (c->carga_horaria_total <=0 ||
        strcmp(c->codigo, "") == 0 ||
        strcmp(temp, "")      == 0 
        )
    {
        // ERRO DE VALIDAÇÃO DOS VALORES PASSADOS
        return -1;
    }

    DAO_list cursos = buscar_cursos();
    for (int i = 0; i < cursos.size; i++)
    {
        Curso * temp_curso = cursos.items[i];
        if (strcmp(temp_curso->codigo, c->codigo) == 0)
        {
            // ERRO AO SALVAR
            return -2;
        }
    }

    salvar_curso(c);

    return 0;
}
int remover_curso_seguro(int id){
    if (existe_curso(id) != 0){
        return -2;
    }

    Curso * temp = buscar_curso(id);
    if (temp->qtd_disciplinas >= 1){
        return -2;        
    }
    
    excluir_curso(id);

    return 0;
}