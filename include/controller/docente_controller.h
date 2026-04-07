#ifndef DOCENTE_CONTROLLER
#define DOCENTE_CONTROLLER

#include "model/docente.h"

int cadastrar_docente(Docente * d);

int logar_docente(char * login, char * senha);

Docente buscar_docente_id(int id);

#endif