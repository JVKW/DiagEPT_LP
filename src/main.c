#include <stdio.h>
#include "view/menu.h"
#include "controller/notas.h"
#include "controller/diagnostico.h"
#include "model/estado.h"
#include "controller/evasao.h"
#include "utils/utils.h"

int main() {
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
            adicionarNotas(&estado);
            break;

        case 2:
            limparTela();
            printf("=== DIAGNOSTICO ===\n");
            mostrarDiagnostico(&estado);
            break;

        case 3:
            limparTela();
            printf("=== REGISTRAR EVASAO ===\n");
            registrarEvasao(&estado);
            break;

        case 4:
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
    } while (opcao != 4);

    return 0;
}