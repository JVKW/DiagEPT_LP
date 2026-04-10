#include "view/curso_view.h"
#include "model/curso.h"
#include <stdio.h>
#include "utils/utils.h"
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





void tela_excluir_curso();
