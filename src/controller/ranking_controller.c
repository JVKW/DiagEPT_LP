#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "controller/ranking_controller.h"
#include "dao/turmaDAO.h"
#include "dao/matriculaDAO.h"

// ======================================================
// FUNÇÃO: calcularMediaAluno
// ======================================================
/*
 * Calcula a média entre nota teórica e prática.
 *
 * Retorna:
 *  - média (0 a 10)
 *  - -1 se o aluno não possui notas válidas
 *
 * Uso:
 *   float media = calcularMediaAluno(m);
 */
float calcularMediaAluno(Matricula *m) {
    if (!m) return -1.0f;

    float soma = 0.0f;
    int qtd = 0;

    if (m->nota_teorica >= 0) {
        soma += m->nota_teorica;
        qtd++;
    }

    if (m->nota_pratica >= 0) {
        soma += m->nota_pratica;
        qtd++;
    }

    if (qtd == 0) return -1.0f;

    return soma / qtd;
}

// ======================================================
// REGRA: validação de aluno para ranking
// ======================================================
static bool alunoValido(Matricula *m) {
    if (!m) return false;

    // entra no ranking apenas se tiver pelo menos uma nota válida
    return !(m->nota_teorica < 0 && m->nota_pratica < 0);
}

// ======================================================
// REGRA: comparação de ranking (ordem decrescente)
// ======================================================
static bool deveTrocar(Matricula *a, Matricula *b) {
    return calcularMediaAluno(a) < calcularMediaAluno(b);
}

// ======================================================
// ORDENAÇÃO DO RANKING
// ======================================================
void ordenarRanking(DAO_list *lista) {
    for (int i = 0; i < lista->size - 1; i++) {
        for (int j = 0; j < lista->size - i - 1; j++) {

            Matricula *a = lista->items[j];
            Matricula *b = lista->items[j + 1];

            if (!a || !b) continue;

            if (deveTrocar(a, b)) {
                void *tmp = lista->items[j];
                lista->items[j] = lista->items[j + 1];
                lista->items[j + 1] = tmp;
            }
        }
    }
}

// ======================================================
// FUNÇÃO: obterRankingMatriculas
// ======================================================
/*
 * Retorna o ranking de alunos de uma turma ordenado por média.
 *
 * REGRAS:
 * - ignora alunos com (-1, -1)
 * - ordena por média decrescente
 * - filtra inconsistências de turma
 *
 * USO:
 *
 *   DAO_list ranking = obterRankingMatriculas(id_turma);
 *
 *   for (int i = 0; i < ranking.size; i++) {
 *       Matricula *m = ranking.items[i];
 *       printf("ID: %d | Media: %.2f\n",
 *              m->id,
 *              calcularMediaAluno(m));
 *   }
 */
DAO_list obterRankingMatriculas(int id_turma) {

    DAO_list lista = {0};

    Turma *t = buscar_turma(id_turma);

    if (!t || t->qtd_matricula <= 0) {
        return lista;
    }

    lista.items = malloc(sizeof(void*) * t->qtd_matricula);

    if (!lista.items) {
        return lista;
    }

    for (int i = 0; i < t->qtd_matricula; i++) {

        int idMat = t->id_matricula[i];

        Matricula *m = buscar_matricula(idMat);

        if (!m) continue;

        if (m->id_turma != id_turma) continue;

        if (!alunoValido(m)) continue;

        lista.items[lista.size++] = m;
    }

    if (lista.size == 0) {
        free(lista.items);
        lista.items = NULL;
        return lista;
    }

    ordenarRanking(&lista);

    return lista;
}

// ======================================================
// FUNÇÃO: obterAlunoDestaque
// ======================================================
/*
 * Retorna o aluno com maior média da turma.
 *
 * USO:
 *
 *   Matricula *d = obterAlunoDestaque(1);
 *
 *   if (d) {
 *       printf("Destaque ID: %d\n", d->id);
 *   }
 */
Matricula* obterAlunoDestaque(int id_turma) {

    DAO_list r = obterRankingMatriculas(id_turma);

    if (!r.items || r.size == 0) {
        free(r.items);
        return NULL;
    }

    Matricula *destaque = r.items[0];

    free(r.items);

    return destaque;
}