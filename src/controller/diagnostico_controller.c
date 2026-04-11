#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "controller/diagnostico_controller.h"
#include "controller/ranking_controller.h"
#include "model/matricula.h"
#include "model/turma.h"
#include "model/diagnostico_turma.h"

#include "dao/turmaDAO.h"
#include "dao/matriculaDAO.h"

// ======================================================
// DEFASAGEM
// ======================================================
static float calcularDefasagemAluno(Matricula *m) {
    if (!m) return 0.0f;
    return (m->aulas_ausente * 45.0f) / 60.0f;
}

// ======================================================
// INIT
// ======================================================
static void inicializarDiagnostico(DiagnosticoTurma *d) {
    d->totalAlunos = 0;
    d->mediaGeral = 0.0f;
    d->taxaEvasao = 0.0f;
    d->defasagemTotal = 0.0f;
    strcpy(d->status, "");
}

// ======================================================
// STATUS
// ======================================================
static void definirStatusDiagnostico(
    DiagnosticoTurma *d,
    int alunosComNota
) {
    if (alunosComNota == 0) {
        strcpy(d->status, "TURMA EM ANDAMENTO");
    }
    else if (d->defasagemTotal > 20.0f) {
        strcpy(d->status, "TURMA COM DEFASAGEM");
    }
    else if (d->mediaGeral >= 7.0f && d->taxaEvasao < 5.0f) {
        strcpy(d->status, "TURMA DESTAQUE");
    }
    else if (d->mediaGeral < 7.0f || d->taxaEvasao > 20.0f) {
        strcpy(d->status, "TURMA COM PROBLEMAS");
    }
    else {
        strcpy(d->status, "TURMA ESTAVEL");
    }
}

// ======================================================
// DIAGNÓSTICO
// ======================================================
DiagnosticoTurma calcularDiagnosticoTurma(int id_turma) {

    Turma *turma = buscar_turma(id_turma);

    DiagnosticoTurma d;
    inicializarDiagnostico(&d);

    if (!turma) {
        strcpy(d.status, "TURMA NAO ENCONTRADA");
        return d;
    }

    float somaMedias = 0.0f;
    int alunosComNota = 0;
    int totalEvasoes = 0;

    for (int i = 0; i < turma->qtd_matricula; i++) {

        Matricula *m = buscar_matricula(turma->id_matricula[i]);

        if (!m) continue;
        if (m->id_turma != id_turma) continue;

        // 🔥 mesma regra do ranking
        if (m->nota_teorica < 0 && m->nota_pratica < 0) {
            continue;
        }

        float media = calcularMediaAluno(m);

        if (media >= 0) {
            somaMedias += media;
            alunosComNota++;
        }

        d.defasagemTotal += calcularDefasagemAluno(m);

        if (m->tem_evasao) {
            totalEvasoes++;
        }

        d.totalAlunos++;
    }

    if (d.totalAlunos == 0) {
        strcpy(d.status, "SEM DADOS");
        return d;
    }

    if (alunosComNota > 0) {
        d.mediaGeral = somaMedias / alunosComNota;
    }

    d.taxaEvasao = (totalEvasoes * 100.0f) / d.totalAlunos;

    definirStatusDiagnostico(&d, alunosComNota);

    return d;
}