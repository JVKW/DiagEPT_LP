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

void adicionar_matricula_na_turma(int id_turma, int id_matricula) {
    Turma * t = buscar_turma(id_turma);

    int novo_tamanho = t->qtd_matricula + 1;
    
    int *matriculas_atuais = malloc(sizeof(int) * novo_tamanho);

    for (int i = 0; i < t->qtd_matricula; i++){
        matriculas_atuais[i] = t->id_matricula[i];
    }

    free(t->id_matricula);

    t->id_matricula = matriculas_atuais;
    t->id_matricula[t->qtd_matricula] = id_matricula;
    t->qtd_matricula = novo_tamanho;

    atulizar_turma(t);

    free(matriculas_atuais);
}

int remover_matricula_na_turma(int id_matricula){
    
    DAO_list turmas = buscar_turmas();
    for (int t = 0; t < turmas.size; t++) {

        Turma *turma = turmas.items[t];

        int pos = -1;

        for (int i = 0; i < turma->qtd_matricula; i++) {
            if (turma->id_matricula[i] == id_matricula) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            continue;
        }

        int novo_tamanho = turma->qtd_matricula - 1;

        if (novo_tamanho == 0) {
            free(turma->id_matricula);
            turma->id_matricula = NULL;
            turma->qtd_matricula = 0;
            continue;
        }

        int *novo_vetor = malloc(sizeof(int) * novo_tamanho);

        for (int i = 0, j = 0; i < turma->qtd_matricula; i++) {
            if (i != pos) {
                novo_vetor[j++] = turma->id_matricula[i];
            }
        }

        free(turma->id_matricula);

        turma->id_matricula = novo_vetor;
        turma->qtd_matricula = novo_tamanho;

        atulizar_turma(turma);
    }

    return 0;
}