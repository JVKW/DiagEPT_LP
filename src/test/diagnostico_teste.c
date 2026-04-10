#include <stdio.h>
#include <stdlib.h>

#include "controller/diagnostico_controller.h"
#include "model/matricula.h"
#include "model/turma.h"
#include "model/diagnostico_turma.h"
#include "dao/matriculaDAO.h"
#include "dao/turmaDAO.h"


// =========================
// MATRÍCULAS
// =========================
void testarLeituraMatriculas() {
    printf("\n===== MATRICULAS =====\n");

    DAO_list lista = buscar_matriculas();

    printf("DEBUG -> size: %d\n", lista.size);
    printf("DEBUG -> items: %p\n", lista.items);

    printf("Total: %d\n", lista.size);

    for (int i = 0; i < lista.size; i++) {
        Matricula *m = (Matricula*) lista.items[i];
        if (!m) continue;

        printf("ID %d | T %.2f | P %.2f | %s\n",
            m->id,
            m->nota_teorica,
            m->nota_pratica,
            m->status
        );
    }
}


// =========================
// RANKING
// =========================
void testarRanking() {
    printf("\n===== RANKING =====\n");

    DAO_list lista = buscar_matriculas();
    ordenarRanking(&lista);

    for (int i = 0; i < lista.size; i++) {
        Matricula *m = (Matricula*) lista.items[i];
        if (!m) continue;

        float media = (m->nota_teorica + m->nota_pratica) / 2.0;

        printf("ID %d -> %.2f\n", m->id, media);
    }
}


// =========================
// DIAGNÓSTICO TURMA
// =========================
void testarDiagnosticoTurma(int id_turma) {
    printf("\n===== DIAGNÓSTICO TURMA =====\n");

    DiagnosticoTurma d = calcularDiagnosticoTurma(id_turma);

    printf("Media Geral: %.2f\n", d.mediaGeral);
    printf("Taxa Evasao: %.2f%%\n", d.taxaEvasao);
    printf("Defasagem: %.2f h\n", d.defasagemTotal);
    printf("Alunos: %d\n", d.totalAlunos);
    printf("Status: %s\n", d.status);
}


// =========================
// MAIN
// =========================
int main() {
    testarLeituraMatriculas();
    testarRanking();
    testarDiagnosticoTurma(1);

    return 0;
}