#include <stdio.h>
#include <stdlib.h>


#include "controller/discente_controller.h"
#include "view/discente_view.h"
#include "model/discente.h"
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

void menu_remover_aluno(){

    puts("\n=== Remossao de Aluno ===");

    printf("\nDigite o id do aluno: ");
    int id = lerInteiro();

    int resultado = excluir_discente_seguro(id);
    if (resultado == 0) {
        puts("Aluno removido com sucesso!");
    }    
}

void listar_todas_discentes(){

    DAO_list lista = listar_discentes();
    for(int i = 0; i < lista.size; i++){
        Discente * temp = lista.items[i];
        printf("ID: %d\n", temp->id);
        printf("Nome: %s\n", temp->nome);
        printf("Matricula: %s\n", temp->numero_matricula);
        printf("\n");
    }
}