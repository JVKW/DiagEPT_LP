#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "controller/diagnostico.h"
#include "model/matricula.h"
#include "model/turma.h"
#include "model/diagnostico_turma.h"

#include "dao/turmaDAO.h"
#include "dao/matriculaDAO.h"


// =========================
// FUNÇÕES AUXILIARES
// =========================
static float mediaAluno(Matricula *m) {
    return (m->nota_teorica + m->nota_pratica) / 2.0;
}

static float defasagemAluno(Matricula *m) {
    return (m->aulas_ausente * 45) / 60.0;
}


// =========================
// RANKING (BUBBLE SORT)
// =========================
void ordenarRanking(DAO_list *lista) {
    for (int i = 0; i < lista->size - 1; i++) {
        for (int j = 0; j < lista->size - i - 1; j++) {

            Matricula *a = (Matricula*) lista->items[j];
            Matricula *b = (Matricula*) lista->items[j + 1];

            if (!a || !b) continue;

            if (mediaAluno(a) < mediaAluno(b)) {
                void *tmp = lista->items[j];
                lista->items[j] = lista->items[j + 1];
                lista->items[j + 1] = tmp;
            }
        }
    }
}


// =========================
// DIAGNÓSTICO DA TURMA
// =========================
DiagnosticoTurma calcularDiagnosticoTurma(int id_turma) {
    Turma *t = buscar_turma(id_turma);

    DiagnosticoTurma d;
    d.totalAlunos = 0;
    d.mediaGeral = 0.0;
    d.taxaEvasao = 0.0;
    d.defasagemTotal = 0.0;

    if (!t) {
        strcpy(d.status, "TURMA NAO ENCONTRADA");
        return d;
    }

    float somaMedias = 0.0;
    int totalEvasao = 0;

    for (int i = 0; i < t->qtd_matricula; i++) {

        Matricula *m = buscar_matricula(t->id_matricula[i]);
        if (!m) continue;

        float media = mediaAluno(m);
        float defasagem = defasagemAluno(m);

        somaMedias += media;
        d.defasagemTotal += defasagem;

        if (m->tem_evasao)
            totalEvasao++;

        d.totalAlunos++;
    }

    if (d.totalAlunos == 0) {
        strcpy(d.status, "SEM DADOS");
        return d;
    }

    d.mediaGeral = somaMedias / d.totalAlunos;
    d.taxaEvasao = (totalEvasao * 100.0) / d.totalAlunos;

    // =========================
    // REGRAS DE STATUS
    // =========================
    if (d.defasagemTotal > 20.0) {
        strcpy(d.status, "TURMA COM DEFASAGEM");
    }
    else if (d.mediaGeral >= 7.0 && d.taxaEvasao < 5.0) {
        strcpy(d.status, "TURMA DESTAQUE");
    }
    else if (d.mediaGeral < 7.0 || d.taxaEvasao > 20.0) {
        strcpy(d.status, "TURMA COM PROBLEMAS");
    }
    else {
        strcpy(d.status, "TURMA ESTAVEL");
    }

    return d;
}


// =========================
// RANKING DE MATRÍCULAS
// =========================
DAO_list obterRankingMatriculas(int id_turma) {
    Turma *t = buscar_turma(id_turma);

    DAO_list lista;
    lista.size = 0;
    lista.items = NULL;

    if (!t) return lista;

    lista.size = t->qtd_matricula;
    lista.items = malloc(sizeof(void*) * lista.size);

    for (int i = 0; i < lista.size; i++) {
        Matricula *m = buscar_matricula(t->id_matricula[i]);

        if (!m) {
            lista.items[i] = NULL;
        } else {
            lista.items[i] = m;
        }
    }

    ordenarRanking(&lista);
    return lista;
}