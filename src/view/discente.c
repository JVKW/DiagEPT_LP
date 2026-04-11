#include <stdio.h>
#include <stdlib.h>
#include "../../include/model/discente.h"
#include "../../include/controller/discente_controller.h"

void menu_registrar_aluno() {
    puts("\n=== Registro de Aluno ===");

    Discente *novo = pede_captura_discente();
    if (novo == NULL) {
        puts("Erro: Falha ao alocar memoria para o aluno.");
        return;
    }

    int resultado = cadastrar_discente(novo);
    if (resultado == 0) {
        puts("Aluno registrado com sucesso!");
    }

    free(novo);
}


