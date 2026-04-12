#include <stdio.h>
#include "view/turma_view.h"
#include "controller/notas_controller.h"
#include "controller/disciplina_controller.h"
#include "controller/docente_controller.h"
#include "model/lista_generica.h"
#include "model/turma.h"
#include "model/disciplina.h"
#include "model/docente.h"

void mostrar_turmas_docente(int id_docente) {
    DAO_list turmas = listar_turmas_professor(id_docente);

    printf("\n=== Turmas do Docente (ID %d) ===\n", id_docente);

    if (!turmas.items || turmas.size == 0) {
        printf("Nenhuma turma encontrada para o docente %d.\n", id_docente);
        return;
    }

    printf("%-12s %-30s %-30s\n", "Codigo", "Disciplina", "Docente");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < turmas.size; i++) {
        Turma *t = (Turma*)turmas.items[i];
        Disciplina disciplina = buscar_disciplina_id(t->id_disciplina);
        Docente docente = buscar_docente_id(t->docente_id);

        const char *nome_disciplina = disciplina.id ? disciplina.nome : "N/D";
        const char *nome_docente = docente.id ? docente.nome : "N/D";

        printf("%-12s %-30s %-30s\n",
               t->codigo,
               nome_disciplina,
               nome_docente);
    }

    free(turmas.items);
}
