#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model/lista_generica.h"

#include "controller/docente_controller.h"
#include "controller/curso_controller.h"
#include "controller/disciplina_controller.h"
#include "controller/turma_controller.h"
#include "controller/discente_controller.h"
#include "controller/matricula_controller.h"

#include "utils/utils.h"
#include "controller/evasao_controller.h"

#include "dao/jsonDAO.h"

#include "view/curso_view.h"

// Quando o usuário estiver logado deve ter o valor 1
// Quando o usuário estiver deslogado deve ter o valor 0
int USUARIO_AUTENTICADO = 0; 


// PADÃO DE CÓDIGOS DE ERRO
/*
     0 Executou sem erros;
    -1 Erro na valição;
*/

int main() {
    // Exemplo de como salvar um dado
    // ISSO DEVE ACONTECER EXCLUSIVAMENTE EM UM ARQUIVO 
    // DA PASTA VIEW

    // Docente d;
    // strcpy(d.nome, "Fulanoo de Tal");
    // strcpy(d.senha, "sadojfoisr");
    // strcpy(d.login, "654927");

    // cadastrar_docente(&d);

    // USUARIO_AUTENTICADO = logar_docente("654927", "sadojfoisr") >= 0? 1: 0;
    
    // printf("%d\n", USUARIO_AUTENTICADO);

    // Curso c;
    // c.id = 3;
    // c.carga_horaria_total = 10;
    // strcpy(c.codigo, "sahfg");
    // strcpy(c.nome, "Disciplina");


    // cadastrar_curso(&c);

    //Disciplina d;

    //d.carga_horaria_total = 40;
    //strcpy(d.codigo, "alsjjre");
    //strcpy(d.nome, "LAB");
    
    //int curso_id = 1;
    //cadastrar_disciplina(&d, curso_id);


    //printf("%d\n",remover_disciplina_seguro(1));
    // Discente xanderson;
    // strcpy(xanderson.nome,"xanderson");
    // xanderson.numero_matricula= 458889;
    // printf("%d \n ", cadastrar_discente(&xanderson));


    // //int result = criar_turma(2,1);
    // Turma * t = buscar_turma(1);
    // printf("%d", excluir_turma_seguro(9));

    realizar_matricula(1, 1);
    processar_evasao_discente(1, "LEDSON");
    // remover_matricula(1);
    
    return 0;
}