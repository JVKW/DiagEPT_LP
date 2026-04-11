#ifndef RANKING_CONTROLLER_H
#define RANKING_CONTROLLER_H

#include <stdbool.h>
#include "model/matricula.h"
#include "model/lista_generica.h"



float calcularMediaAluno(Matricula *m);

void ordenarRanking(DAO_list *lista);

DAO_list obterRankingMatriculas(int id_turma);

Matricula* obterAlunoDestaque(int id_turma);

bool turmaEhDestaque(int id_turma);

#endif