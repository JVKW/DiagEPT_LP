#include "controller/disciplina_controller.h"
#include <stdio.h>
#include "utils/utils.h"
#include "dao/cursoDAO.h"
#include "view/disciplina_view.h"
#include <stdlib.h>


void menu_disciplina(){

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

void menu_atualizar_disciplina() {
    int id;

    printf("ID da disciplina a ser atualizada: ");
    id = lerInteiro();

    int removeu = remover_disciplina_seguro(id);

    if (removeu != 0) {
        printf("Erro ao remover disciplina!\n");
        return ;
    }

    Disciplina nova;
    int curso_id;

    printf("ID do curso: ");
    curso_id = lerInteiro();

    printf("Nome: ");

    lerString(nova.nome, 128);

    printf("Codigo: ");
    lerString(nova.codigo, 16);

    printf("Carga horaria: ");
    nova.carga_horaria_total = lerInteiro();

    nova.id_turma = NULL;
    nova.qtd_turma = 0;

    int resultado = cadastrar_disciplina(&nova, curso_id);

    if (resultado == 0) {
        printf("Erro ao atualizar!\n");
    } else {
        printf("Disciplina atualizada com sucesso!\n");
    }
}

