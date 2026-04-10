#ifndef DISCIPLINA_CONTROLLER
#define DISCIPLINA_CONTROLLER

#include "model/disciplina.h"

int cadastrar_disciplina(Disciplina *d, int id_disciplina);

int atulizar_turmas(int id, int *id_turma, int qtd_turma);

int remover_disciplina_seguro(int id);

void adicionar_turma_na_disciplina(int id_disciplina, int nova_turma_id);

int remover_turma_na_disciplina(int id_disciplina, int turma_id);

#endif