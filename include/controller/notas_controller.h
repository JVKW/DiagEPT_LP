#ifndef NOTAS_H
#define NOTAS_H

#include "model/estado.h"
#include "model/lista_generica.h"
#include "model/matricula.h"

DAO_list listar_turmas_professor(int id_docente);

DAO_list listar_matriculas_turma(int id_turma);

const char* obter_nome_discente_por_matricula(Matricula *m);

#endif