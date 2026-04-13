#ifndef CURSODAO_H
#define CURSODAO_H


#include "dao/jsonDAO.h"
#include "json_mapper/curso_mapper.h"
#include "model/curso.h"
#include "model/lista_generica.h"


#define CURSO_FILE "data/curso.json"

void salvar_curso(Curso *d);

Curso *buscar_curso(int id);

DAO_list buscar_cursos( );

void excluir_curso(int id);

void atualizar_curso(Curso *d);

int existe_curso(int id);

void tela_listar_cursos( );

#endif