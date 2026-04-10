#ifndef CURSOCONTROLLER
#define CURSOCONTROLLER

#include "model/curso.h"

int cadastrar_curso(Curso *c);
int remover_curso_seguro(int id);
int adicionar_disciplina(int id_curso, int id_disciplina);

#endif