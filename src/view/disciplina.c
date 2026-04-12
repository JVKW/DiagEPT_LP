#include <stdio.h>
#include "../include/dao/disciplinaDAO.h"
#include "../include/model/disciplina.h"
#include "../include/model/lista_generica.h"

void listar_todas_disciplinas(){

    DAO_list lista = buscar_disciplinas();
    for(int i = 0; i < lista.size; i++){
        Disciplina * temp = lista.items[i];
        printf("ID: %d\n", temp->id);
        printf("Nome: %s\n", temp->nome);
        printf("Codigo: %s\n", temp->codigo);
        printf("Carga Horaria Total: %d\n", temp->carga_horaria_total);
        printf("Quantidade de Turmas: %d\n", temp->qtd_turma);
        printf("\n");
    }
}