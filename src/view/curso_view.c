#include "view/curso_view.h"
#include "model/curso.h"
#include <stdio.h>
#include "utils/utils.h"
#include "dao/cursoDAO.h"
#include "controller/curso_controller.h"



void tela_cadastrar_curso(){

    Curso novo;
    printf("Indique o nome do curso : \n ");
    lerString(novo.nome, 128 );
    printf("Indique o codigo do curso : \n ");
    lerString(novo.codigo , 16 );
    printf("Indique a carga horaria : \n ");
    novo.carga_horaria_total = lerInteiro();
    novo.id_disciplinas=NULL;
    novo.qtd_disciplinas = 0;
    
    int resultado = cadastrar_curso(&novo);
    printf((resultado == 0 ? "Sucesso no cadastro! \n " : "Falha no cadastro :( valores invalidos ! \n)"));


}



//Criar uma função void tela_excluir_curso().
//
//Solicite o id do curso;
//
//Use a função remover_curso_seguro(id); (lembre de importar o curso_controller.h)
//
//Se a função retornar 0 informe que houve sucesso ao realizar a ação; do contrário, informe que houve um erro.

void tela_excluir_curso(){

    printf("Informe o id do curso que você gostaria de remover : \n ");

    int id;
    scanf("%d",&id);
   
    int resultado = remover_curso_seguro(id);

    
    printf((resultado == 0 ?  "Sucesso na remoção! o curso Foi removido !! \n "  : "Erro na remoção do curso !! esse curso não existe .... \n " ));

    remover_curso_seguro(id);


}
