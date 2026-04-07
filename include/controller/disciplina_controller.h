#ifndef DISCIPLINA_CONTROLLER
#define DISCIPLINA_CONTROLLER

#include "model/disciplina.h"

void cadastrar_disciplina(char nome[256], int numero_matricula);

Disciplina buscar_disciplina_id(int id);

#endif