#include <string.h>

#include "dao/matriculaDAO.h"
#include "dao/turmaDAO.h"
#include "controller/turma_controller.h"
#include "controller/matricula_controller.h"



int realizar_matricula(int id_discente, int id_turma){
    if (existe_turma(id_turma) != 0){
        return -1;
    }

    Turma *t = buscar_turma(id_turma);
    for (int i = 0; i < t->qtd_matricula; i++)
    {
        if (existe_matricula(t->id_matricula[i]) != 0)
        {
            continue;
        }

        Matricula * temp_matricula = buscar_matricula(t->id_matricula[i]);

        if (temp_matricula->discente_id == id_discente){
            return -1;
        }
    }

    Matricula m;
    m.id = dao_next_id(MATRICULA_FILE);
    m.aulas_ausente = 0;
    m.discente_id = id_discente;
    m.id_turma = id_turma;
    m.nota_teorica = -1; //Valor negativo indicando que ainda não foi informado pelo docente
    m.nota_pratica = -1; 
    m.tem_evasao = false;
    m.tempo_ausente = 0;
    m.id_evasao = -1; // Valor negativo indicando que ainda não foi informado pelo docente

    strcpy(m.status, "MATRICULADO");
    
    salvar_matricula(&m);

    adicionar_matricula_na_turma(id_turma, m.id);

    return 0;
}


int remover_matricula(int id_matricula){

    remover_matricula_na_turma(id_matricula);

    excluir_matricula(id_matricula);

    return 0;
}