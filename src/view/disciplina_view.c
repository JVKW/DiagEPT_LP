#include "controller/disciplina_controller.h"
#include <stdio.h>
#include "utils/utils.h"
#include "dao/cursoDAO.h"
#include "view/disciplina_view.h"

void menu_cadastrar_disciplina(){

    Disciplina novo;

    int curso_id;

    printf("Qual o id do curso? \n ");

    scanf("%d", curso_id );

    printf("Qual o nome do curso ? \n ");

    int nome_curso;

    scanf("%d",nome_curso);

    printf("Qual o codigo do curso ? \n ");

    int novo_codigo;

    scanf("%d",novo_codigo);

    printf("Qual a carga horaria do curso ? \n ");
    
    int nova_carga_horaria_total;

    scanf("%d", nova_carga_horaria_total);
    
    novo.id_turma = NULL;

    novo.qtd_turma = 0;

    int resultado = cadastrar_disciplina(&novo, curso_id);

    if (resultado == 0) {

        printf("Sucesso no cadastro !! \n ");

    }else{
        
        printf("Falha no cadastro :(( \n  ");
    }



}