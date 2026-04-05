#ifndef DOCENTE_CONTROLLER
#define DOCENTE_CONTROLLER

#include "model/docente.h"

void cadastrarDocente(char nome[256], char login[256], char senha[128]);

Docente buscarDocentePorId(int id);

#endif