#include <stdio.h>
#include <string.h>

#include "view/menu.h"
#include "view/diagnostico.h"

#include "model/estado.h"
#include "model/estado.h"
#include "model/lista_generica.h"

#include "controller/evasao.h"
#include "controller/notas.h"
#include "controller/discente_controller.h"
#include "controller/docente_controller.h"

#include "utils/utils.h"

#include "dao/jsonDAO.h"

// Quando o usuário estiver logado deve ter o valor 1
// Quando o usuário estiver deslogado deve ter o valor 0
int USUARIO_AUTENTICADO = 0; 

void menu(){
    int opcao;
    Estado estado;

    inicializarEstado(&estado);

    const char *menuPrincipal =
    "=== MENU ===\n"
    "1 - Adicionar notas\n"
    "2 - Ver diagnostico\n"
    "3 - Registrar evasao\n"
    "4 - Sair\n";

    do {
        opcao = mostrarMenu(menuPrincipal, 1);

        switch (opcao) {
        case 1:
            limparTela();
            printf("=== ADICIONAR NOTAS ===\n");
            adicionar_notas(&estado);
            break;

        case 2:
            limparTela();
            printf("=== DIAGNOSTICO ===\n");
            mostrarDiagnostico(&estado);
            break;

        case 3:
            limparTela();
            printf("=== REGISTRAR EVASAO ===\n");
            registrar_evasao(&estado);
            break;

        case 4:
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar(); // espera o usuário

    } while (opcao != 4);
}

// PADÃO DE CÓDIGOS DE ERRO
/*
     0 Executou sem erros;
    -1 Erro na valição 
*/

int main() {
    // Exemplo de como salvar um dado
    Docente d;
    //d.id = 2;
    strcpy(d.nome, "Fulanoo de Tal");
    strcpy(d.senha, "sadojfoisr");
    strcpy(d.login, "654927");

    //cadastrar_docente(&d);

    USUARIO_AUTENTICADO = logar_docente("654927", "sadojfoisr") >= 0? 1: 0;
    
    printf("%d\n", USUARIO_AUTENTICADO);

    //update_discente_id(&d);
    //puts(docentes[1].nome);




    return 0;
}