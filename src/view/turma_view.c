#include <stdio.h>
#include "../include/model/lista_generica.h"
#include "../include/model/disciplina.h"
#include "../include/model/turma.h"
#include "../include/controller/turma_controller.h"
#include "../include/dao/turmaDAO.h"
#include "../include/dao/disciplinaDAO.h"
#include "../include/controller/docente_controller.h"
#include "../include/dao/docenteDAO.h"
#include "../include/model/docente.h"
#include "../include/utils/utils.h"

void fluxo_de_selecao_de_turma(){
    printf("\nDisciplinas cadastradas:\n");
    DAO_list disciplinas = buscar_disciplinas();

    for(int i = 0; i < disciplinas.size; i++){
        Disciplina * temp = disciplinas.items[i];
        printf("  ID: %d - Nome: %s\n", temp->id, temp->nome);
    }

    printf("Selecione o ID da disciplina: ");
    int id_disciplina = lerInteiro();
    Disciplina * disciplina = buscar_disciplina(id_disciplina);
    if(disciplina == NULL){
        printf("\nDisciplina não encontrada.\n");
        return;
    }

    DAO_list docentes = buscar_docentes();
    printf("\nDocentes cadastrados:\n");
    for(int i = 0; i < docentes.size; i++){
        Docente * temp = docentes.items[i];
        printf("  ID: %d - Nome: %s\n", temp->id, temp->nome);
    }

    printf("Selecione o ID do docente: ");
    int id_docente = lerInteiro();
    Docente * docente = buscar_docente(id_docente);
    if(docente == NULL){
        printf("\nDocente não encontrado.\n");
        return;
    }

    int id_turma = criar_turma(id_disciplina, id_docente);
    if(id_turma >= 0){
        printf("Turma T-%03d criada com sucesso!\n", id_turma);
    } else {
        printf("Erro ao criar a turma.\n");
    }
}

void fluxo_excluir_turma(){
    printf("\nInforme o ID da turma que será excluída: ");
    int id_turma = lerInteiro();

    int resultado = excluir_turma_seguro(id_turma);
    if(resultado == 0){
        printf("Turma %d excluída com sucesso!\n", id_turma);
    } else {
        printf("Não foi possível excluir a turma %d.\n", id_turma);
    }
}

