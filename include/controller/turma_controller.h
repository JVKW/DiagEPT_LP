#ifndef TURMACONTROLLER
#define TURMACONTROLLER

#include "model/turma.h"

int criar_turma(int id_disciplina, int id_docente);

int excluir_turma_seguro(int id);

void adicionar_matricula_na_turma(int id_turma, int id_matricula);

int remover_matricula_na_turma(int id_matricula);

#endif