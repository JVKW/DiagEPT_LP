#ifndef DISCIPLINA_CONTROLLER
#define DISCIPLINA_CONTROLLER

#include "model/disciplina.h"

int cadastrar_disciplina(Disciplina *d, int id_disciplina);

int atulizar_turmas(int id, int *id_turma, int qtd_turma);

int remover_disciplina_seguro(int id);

#endif