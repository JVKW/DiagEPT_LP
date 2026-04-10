#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H

#include <stdbool.h>

#include "model/diagnostico_turma.h"
#include "model/estado.h"

#include "dao/matriculaDAO.h"

const char* calcularStatusTurma(Estado *e, float defasagemTotal, bool temDefasagem);
const char* obterStatusTurma(Estado *e, float defasagemTotal, bool temDefasagem);
void ordenarRanking(DAO_list *lista);
void atualizarIndicadores(Estado *e, Matricula *m);
Estado calcularIndicadores();
DiagnosticoTurma calcularDiagnosticoTurma(int id_turma);

#endif