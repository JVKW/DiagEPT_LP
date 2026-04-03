#include <stdio.h>
#include <stdlib.h>
#include "view/menu.h"
#include "utils/utils.h"

#define SEM_OPCAO 0
#define COM_OPCAO 1

void imprimirMenu(const char *menu) {
    printf("%s\n", menu);
}

int lerOpcao() {
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);

    return atoi(buffer);
}

int mostrarMenu(const char *menu, int opc) {
    imprimirMenu(menu);

    if (opc) {
        printf("Escolha: ");
        return lerOpcao();
    }

    return -1;
}