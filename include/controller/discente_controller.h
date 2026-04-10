#ifndef DISCENTE_CONTROLLER
#define DISCENTE_CONTROLLER

#include "model/discente.h"

int cadastrar_discente(Discente *);

Discente buscar_discente_id(int id);

void update_discente_id(Discente *d);

#endif