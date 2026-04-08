#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model/lista_generica.h"

#include "controller/docente_controller.h"
#include "controller/curso_controller.h"

#include "utils/utils.h"

#include "dao/jsonDAO.h"

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

    Curso c;
    c.id = 3;
    c.carga_horaria_total = 10;
    strcpy(c.codigo, "sahfg");
    strcpy(c.nome, "Disciplina");


    cadastrar_curso(&c);

    

    


    printf("%d\n",remover_curso_seguro(4));

        
    return 0;
}