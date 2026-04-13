#include "controller/disciplina_controller.h"
#include <stdio.h>
#include "utils/utils.h"
#include "dao/cursoDAO.h"
#include "dao/disciplinaDAO.h"
#include "view/disciplina_view.h"
#include <stdlib.h>


void menu_cadastrar_disciplina(){

    Disciplina novo;

    
    printf("Qual o id do curso? \n ");
    
    int id_curso = lerInteiro();

    printf("Qual o nome da disciplina ? \n ");

    lerString(novo.nome, 128);

    printf("Qual o codigo da disciplina ? \n ");

    lerString(novo.codigo, 16);


    printf("Qual a carga horaria da disciplina ? \n ");
    
    novo.carga_horaria_total = lerInteiro();
    
    novo.id_turma = NULL;

    novo.qtd_turma = 0;

    int resultado = cadastrar_disciplina(&novo, id_curso);


    if (resultado == 0) {

        printf("Sucesso ao cadastrar disciplina!! \n ");

    }else{
        
        printf("Falha ao cadastrar disciplina :( \n  ");
    }
}



void menu_remover_disciplina(){

    printf("Digite o ID da disciplina a ser removida! \n");

    int id = lerInteiro();

    int resultado = remover_disciplina_seguro(id);


    if (resultado ==0 ){
        printf("Disciplina Removida com sucesso !! \n ");

    }else{
        printf("Erro ao remover disciplina esse id de disciplina nao existe.... \n " );
    }

    }

void listar_todas_disciplinas(){

    DAO_list lista = buscar_disciplinas();
    for(int i = 0; i < lista.size; i++){
        Disciplina * temp = lista.items[i];
        printf("ID: %d\n", temp->id);
        printf("Nome: %s\n", temp->nome);
        printf("Codigo: %s\n", temp->codigo);
        printf("Carga Horaria Total: %d\n", temp->carga_horaria_total);
        printf("Quantidade de Turmas: %d\n", temp->qtd_turma);
        printf("\n");
    }
}
