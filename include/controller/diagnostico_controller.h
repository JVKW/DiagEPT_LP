#ifndef DIAGNOSTICO_CONTROLLER_H
#define DIAGNOSTICO_CONTROLLER_H

#include "model/diagnostico_turma.h"
#include "dao/matriculaDAO.h"

void ordenarRanking(DAO_list *lista);
DiagnosticoTurma calcularDiagnosticoTurma(int id_turma);
DAO_list obterRankingMatriculas(int id_turma);

#endif