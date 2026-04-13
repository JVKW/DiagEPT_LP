#ifndef EVASAO_CONTROLLER_H
#define EVASAO_CONTROLLER_H

#include "model/estado.h"

void registrarEvasao(Estado *e);

int processar_evasao_discente(int id_matricula, char *motivo);

#endif