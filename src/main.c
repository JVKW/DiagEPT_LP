#include <stdio.h>
#include <string.h>

#include "view/menu.h"
#include "controller/notas.h"
#include "view/diagnostico.h"
#include "model/estado.h"
#include "controller/evasao.h"
#include "utils/utils.h"
#include "model/estado.h"
#include "controller/discente_controller.h"

#include "dao/jsonDAO.h"

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

int main() {
    // Exemplo de como salvar um dado
    Discente d;
    d.id = 2;
    strcpy(d.nome, "Fulanoo de Tal");
    d.numero_matricula = 654627;

    update_discente_id(&d);


    return 0;
}