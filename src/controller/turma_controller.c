#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "controller/turma_controller.h"
#include "controller/disciplina_controller.h"
#include "dao/turmaDAO.h"
#include "dao/disciplinaDAO.h"
#include "dao/docenteDAO.h"
#include "dao/matriculaDAO.h"


int criar_turma(int id_disciplina, int id_docente){
    int verifica_disciplina = existe_disciplina(id_disciplina);
    int verifica_docente    = existe_docente(id_docente);
    
    if (verifica_disciplina != 0 || verifica_docente != 0)
    {
        return -1;
    }

    Turma t;
    t.id_disciplina = id_disciplina;

    // Gerando código da turma
    int id_turma = dao_next_id(TURMA_FILE);

    char * cod_turma = malloc(9);
    char * num = malloc(sizeof(99999));

    sprintf(num, "%d", id_turma);

    int zeros = 7 - strlen(num);

    int pos = sprintf(cod_turma, "T");

    for (int i = 0; i < zeros; i++) {
        cod_turma[pos++] = '0';
    }
    for (int i = 0; i < strlen(num); i++){
        cod_turma[pos++] = num[i];
    }

    strcpy(t.codigo, cod_turma);
    free(cod_turma);

    t.docente_id = id_docente;
    t.id_matricula = NULL;
    t.qtd_matricula = 0;
    
    salvar_turma(&t);

    adicionar_turma_na_disciplina(id_disciplina, id_turma);

}
int excluir_turma_seguro(int id){
    if (existe_turma(id) != 0)
    {
        return -1;
    }
    
    Turma *t = buscar_turma(id);
    if(t->qtd_matricula > 0){
        for(int i; i < t->qtd_matricula; i++){
            Matricula * m = buscar_matricula(t->id_matricula[i]);
            if (m->tem_evasao != true)
            {
                return -1;
            }            
        }
    }

    if (remover_turma_na_disciplina(t->id_disciplina, id) != 0)
    {
        return -1;
    }

    excluir_turma(id);
    
    return 0;
}