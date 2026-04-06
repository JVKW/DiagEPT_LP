#ifndef DISCENTE_CONTROLLER
#define DISCENTE_CONTROLLER

#include "model/discente.h"

void cadastrarDiscente(char nome[256], int numero_matricula);

Discente buscarDiscentePorId(int id);

#endif