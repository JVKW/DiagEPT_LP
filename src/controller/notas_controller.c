#include <stdlib.h>
#include <stdio.h>

#include "controller/notas_controller.h"

#include "dao/turmaDAO.h"
#include "dao/matriculaDAO.h"
#include "dao/discenteDAO.h"
#include "dao/docenteDAO.h"

#include "model/turma.h"
#include "model/matricula.h"
#include "model/discente.h"
#include "model/lista_generica.h"

// ======================================================
// FUNÇÃO: listar_turmas_professor
// ======================================================
/*
 * Retorna todas as turmas de um docente específico.
 *
 * USO:
 *   DAO_list turmas = listar_turmas_professor(1);
 *
 *   for (int i = 0; i < turmas.size; i++) {
 *       Turma *t = turmas.items[i];
 *       printf("Turma ID: %d\n", t->id);
 *   }
 */
DAO_list listar_turmas_professor(int id_docente) {

    DAO_list todas = dao_find_all(
        TURMA_FILE,
        json_to_turma
    );

    DAO_list filtradas = {0};

    if (!todas.items || todas.size == 0) {
        return filtradas;
    }

    filtradas.items = malloc(sizeof(void*) * todas.size);

    if (!filtradas.items) {
        if (todas.items) {
            free(todas.items);
        }
        return filtradas;
    }

    for (int i = 0; i < todas.size; i++) {

        Turma *t = (Turma*) todas.items[i];

        if (!t) continue;

        if (t->docente_id == id_docente) {
            filtradas.items[filtradas.size++] = t;
        }
    }

    if (filtradas.size == 0) {
        free(filtradas.items);
        filtradas.items = NULL;
    }

    if (todas.items) {
        free(todas.items);
    }

    return filtradas;
}


// ======================================================
// FUNÇÃO: listar_matriculas_turma
// ======================================================
/*
 * Retorna todas as matrículas de uma turma.
 *
 * USO:
 *   DAO_list mats = listar_matriculas_turma(1);
 *
 *   for (int i = 0; i < mats.size; i++) {
 *       Matricula *m = mats.items[i];
 *       printf("Matricula ID: %d\n", m->id);
 *   }
 */
DAO_list listar_matriculas_turma(int id_turma) {

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

        lista.items[lista.size++] = m;
    }

    if (lista.size == 0) {
        free(lista.items);
        lista.items = NULL;
    }

    return lista;
}


// ======================================================
// FUNÇÃO: obter_nome_discente_por_matricula
// ======================================================
/*
 * Retorna o nome do aluno associado a uma matrícula.
 *
 * USO:
 *   char *nome = obter_nome_discente_por_matricula(m);
 *   printf("Aluno: %s\n", nome);
 *
 * OBS: ponteiro interno (não dar free)
 */
const char* obter_nome_discente_por_matricula(Matricula *m) {

    if (!m) return "DESCONHECIDO";

    Discente *d = buscar_discente(m->discente_id);

    if (!d) return "DESCONHECIDO";

    return d->nome;
}