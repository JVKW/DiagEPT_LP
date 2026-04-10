#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view/menu.h"
#include "controller/notas.h"
#include "controller/diagnostico.h"
#include "model/estado.h"
#include "controller/evasao_controller.h"
#include "utils/utils.h"
#include "dao/discenteDAO.h"

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
    // Discente d;
    // strcpy(d.nome, "Siclano de Tal");
    // d.numero_matricula = 654627;

    // salvar_discente(&d);

    return 0;
}