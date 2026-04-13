#ifndef DISCENTE_CONTROLLER
#define DISCENTE_CONTROLLER

#include "dao/matriculaDAO.h"
#include "model/discente.h"

int cadastrar_discente(Discente *);

Discente buscar_discente_id(int id);

void update_discente_id(Discente *d);

int excluir_discente_seguro(int id_discente);

#endif