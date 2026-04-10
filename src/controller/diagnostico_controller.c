#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "controller/diagnostico_controller.h"
#include "model/matricula.h"
#include "model/turma.h"
#include "model/diagnostico_turma.h"

#include "dao/turmaDAO.h"
#include "dao/matriculaDAO.h"


// ======================================================
// REGRAS DE NEGÓCIO AUXILIARES
// ======================================================

static bool possuiNotaValida(float nota) {
    return nota >= 0;
}

static bool alunoPossuiAlgumaNota(Matricula *m) {
    return possuiNotaValida(m->nota_teorica) ||
        possuiNotaValida(m->nota_pratica);
}

static float calcularMediaAluno(Matricula *m) {
    float soma = 0.0f;
    int quantidadeNotas = 0;

    if (possuiNotaValida(m->nota_teorica)) {
        soma += m->nota_teorica;
        quantidadeNotas++;
    }

    if (possuiNotaValida(m->nota_pratica)) {
        soma += m->nota_pratica;
        quantidadeNotas++;
    }

    if (quantidadeNotas == 0) {
        return -1.0f;
    }

    return soma / quantidadeNotas;
}

static float calcularDefasagemAluno(Matricula *m) {
    return (m->aulas_ausente * 45.0f) / 60.0f;
}


// ======================================================
// REGRAS DE ORDENAÇÃO
// ======================================================

static bool deveTrocarRanking(Matricula *atual, Matricula *proximo) {
    float mediaAtual = calcularMediaAluno(atual);
    float mediaProximo = calcularMediaAluno(proximo);

    bool atualSemNota = (mediaAtual < 0);
    bool proximoSemNota = (mediaProximo < 0);

    if (atualSemNota && !proximoSemNota) {
        return true;
    }

    if (!atualSemNota && !proximoSemNota && mediaAtual < mediaProximo) {
        return true;
    }

    return false;
}

/**
 * Ordena uma lista de matrículas por média decrescente.
 *
 * Exemplo de uso:
 * ----------------------------------
 * DAO_list lista = buscar_matriculas();
 * ordenarRanking(&lista);
 * ----------------------------------
 */
void ordenarRanking(DAO_list *lista) {
    for (int i = 0; i < lista->size - 1; i++) {
        for (int j = 0; j < lista->size - i - 1; j++) {

            Matricula *atual   = (Matricula*) lista->items[j];
            Matricula *proximo = (Matricula*) lista->items[j + 1];

            if (!atual || !proximo) {
                continue;
            }

            if (deveTrocarRanking(atual, proximo)) {
                void *temp = lista->items[j];
                lista->items[j] = lista->items[j + 1];
                lista->items[j + 1] = temp;
            }
        }
    }
}


// ======================================================
// DIAGNÓSTICO DA TURMA
// ======================================================

static void inicializarDiagnostico(DiagnosticoTurma *d) {
    d->totalAlunos = 0;
    d->mediaGeral = 0.0f;
    d->taxaEvasao = 0.0f;
    d->defasagemTotal = 0.0f;
    strcpy(d->status, "");
}

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

/**
 * Calcula o diagnóstico completo de uma turma.
 *
 * Exemplo de uso na View:
 * ----------------------------------
 * DiagnosticoTurma d = calcularDiagnosticoTurma(1);
 *
 * printf("Media Geral: %.2f\n", d.mediaGeral);
 * printf("Taxa Evasao: %.2f%%\n", d.taxaEvasao);
 * printf("Defasagem: %.2f h\n", d.defasagemTotal);
 * printf("Status: %s\n", d.status);
 * ----------------------------------
 */

DiagnosticoTurma calcularDiagnosticoTurma(int id_turma) {
    Turma *turma = buscar_turma(id_turma);

    DiagnosticoTurma diagnostico;
    inicializarDiagnostico(&diagnostico);

    if (!turma) {
        strcpy(diagnostico.status, "TURMA NAO ENCONTRADA");
        return diagnostico;
    }

    float somaMedias = 0.0f;
    int alunosComNota = 0;
    int totalEvasoes = 0;

    for (int i = 0; i < turma->qtd_matricula; i++) {
        Matricula *matricula = buscar_matricula(turma->id_matricula[i]);

        if (!matricula) {
            continue;
        }

        // garante consistência entre turma e matrícula
        if (matricula->id_turma != id_turma) {
            continue;
        }

        float media = calcularMediaAluno(matricula);

        if (media >= 0) {
            somaMedias += media;
            alunosComNota++;
        }

        diagnostico.defasagemTotal += calcularDefasagemAluno(matricula);

        if (matricula->tem_evasao) {
            totalEvasoes++;
        }

        diagnostico.totalAlunos++;
    }

    if (diagnostico.totalAlunos == 0) {
        strcpy(diagnostico.status, "SEM DADOS");
        return diagnostico;
    }

    if (alunosComNota > 0) {
        diagnostico.mediaGeral = somaMedias / alunosComNota;
    }

    diagnostico.taxaEvasao =
        (totalEvasoes * 100.0f) / diagnostico.totalAlunos;

    definirStatusDiagnostico(&diagnostico, alunosComNota);

    return diagnostico;
}


// ======================================================
// RANKING DA TURMA
// ======================================================

/**
 * Retorna ranking ordenado das matrículas de uma turma.
 *
 * Exemplo de uso na View:
 * ----------------------------------
 * DAO_list ranking = obterRankingMatriculas(1);
 *
 * for (int i = 0; i < ranking.size; i++) {
 *     Matricula *m = (Matricula*) ranking.items[i];
 *     printf("Aluno ID: %d\n", m->id);
 * }
 * ----------------------------------
 */
DAO_list obterRankingMatriculas(int id_turma) {
    Turma *turma = buscar_turma(id_turma);

    DAO_list lista = {
        .size = 0,
        .items = NULL
    };

    if (!turma) {
        return lista;
    }

    lista.items = malloc(sizeof(void*) * turma->qtd_matricula);

    for (int i = 0; i < turma->qtd_matricula; i++) {
        Matricula *matricula = buscar_matricula(turma->id_matricula[i]);

        if (!matricula) {
            continue;
        }

        if (matricula->id_turma != id_turma) {
            continue;
        }

        lista.items[lista.size++] = matricula;
    }

    ordenarRanking(&lista);

    return lista;
}