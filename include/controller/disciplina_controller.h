#ifndef DISCIPLINA_CONTROLLER
#define DISCIPLINA_CONTROLLER

#include "model/disciplina.h"

void cadastrar_disciplina(char nome[256], int numero_matricula);

int atulizar_turmas(int id, int *id_turma, int qtd_turma);

#endif