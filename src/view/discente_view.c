#include <stdio.h>
#include <stdlib.h>

#include "model/discente.h"
#include "controller/discente_controller.h"
#include "utils/utils.h"

void menu_registrar_aluno() {
    puts("\n=== Registro de Aluno ===");

    Discente *novo = malloc(sizeof(Discente));

    printf("\nDigite o nome do aluno: ");
    lerString(novo->nome, 256);

    printf("\nDigite o número de matrícula do aluno: ");
    novo->numero_matricula = lerInteiro();

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


