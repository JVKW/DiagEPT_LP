#include <stdio.h>
#include <string.h>
#include "utils/utils.h"
#include "controller/evasao_controller.h"
#include "dao/matriculaDAO.h"
#include "dao/discenteDAO.h"
#include "model/lista_generica.h"

void registrarEvasaoView() {
    // Listar alunos e matrículas
    printf("=== LISTA DE ALUNOS E MATRICULAS ===\n");
    DAO_list matriculas = buscar_matriculas();
    for (int i = 0; i < matriculas.size; i++) {
        Matricula *m = (Matricula *)matriculas.items[i];
        Discente *d = buscar_discente(m->discente_id);
        if (d != NULL) {
            printf("ID Matricula: %d - Nome: %s\n", m->id, d->nome);
        }
    }
    // Liberar memória se necessário, mas assumindo que DAO_list cuida disso

    // Inputs
    printf("ID da Matricula do aluno evadido: ");
    int id_matricula = lerInteiro();

    char motivo[2048];
    printf("Motivo da evasao: ");
    lerString(motivo, 2048);

    // Execução
    int resultado = processar_evasao_discente(id_matricula, motivo);
    if (resultado == 0) {
        printf("Evasao registrada com sucesso!\n");
    } else {
        printf("Erro ao registrar evasao. Verifique o ID da matricula.\n");
    }
}