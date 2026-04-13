#ifndef DISCENTE_CONTROLLER
#define DISCENTE_CONTROLLER

#include "model/discente.h"
#include "model/lista_generica.h"

int cadastrar_discente(Discente *);

DAO_list listar_discentes();

Discente buscar_discente_id(int id);

void update_discente_id(Discente *d);

int remover_discente(int id);

#endif