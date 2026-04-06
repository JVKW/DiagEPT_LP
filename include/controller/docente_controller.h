#ifndef DOCENTE_CONTROLLER
#define DOCENTE_CONTROLLER

#include "model/docente.h"

void cadastrar_docente(char nome[256], char login[256], char senha[128]);

Docente buscar_docente_id(int id);

#endif