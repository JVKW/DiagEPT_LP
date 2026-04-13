#include <stdio.h>
#include <string.h>
#include <stdlib.h>
          
#include "model/matricula.h"        
#include "model/discente.h"         
#include "model/turma.h"             
#include "model/disciplina.h"        

#include "controller/discente_controller.h"
#include "controller/turma_controller.h"
#include "controller/disciplina_controller.h"

#include "dao/matriculaDAO.h"
#include "dao/turmaDAO.h"
#include "dao/discenteDAO.h"
#include "dao/disciplinaDAO.h"

#include "view/notas_view.h"

#include "model/lista_generica.h"

#include "utils/utils.h"

int menu_lancar_notas(int id_docente) {
    int turma_id;

    puts("Digite o ID da turma: ");
    turma_id = lerInteiro();
    puts("Informe o ID da matricula do aluno:");
    int id_matricula = lerInteiro();

    Turma * turma_alvo = buscar_turma(turma_id);
    if(turma_alvo == NULL){
        puts("Erro: Turma não encontrada");
        return -1;
    }
    if(turma_alvo->docente_id != id_docente){
        puts("Erro: Essa turma não pertence ao docente informado");
        return -1;
    }


    DAO_list lista = buscar_matriculas();

    for (int i = 0; i < lista.size; i++) {
        Matricula *m = (Matricula *) lista.items[i];

        if (m->id_turma != turma_id || id_matricula != m->id) continue;

        Discente *d = buscar_discente(m->discente_id);



        printf("\nAluno: %s\n", d->nome);

        printf("Nota teorica: ");
        m->nota_teorica = lerNotaValida();

        printf("Nota pratica: ");
        m->nota_pratica = lerNotaValida();

        printf("Faltas: ");
        int faltas = lerInteiro();

        Turma *t = buscar_turma(m->id_turma);
        Disciplina *disc = buscar_disciplina(t->id_disciplina);

        if (faltas > disc->carga_horaria_total) {
            printf("Erro: Quantidade de faltas superior à carga horaria!\n");
            return -1;
            continue; 
        }

        m->aulas_ausente = faltas;

        
        float media = (m->nota_teorica + m->nota_pratica) / 2;

        if (media >= 7.0) {
            strcpy(m->status, "APROVADO");
        } else {
            strcpy(m->status, "REPROVADO");
        }

        update_matricula(m);

        printf("Dados atualizados!\n");

        printf("ID Matricula: %d\n", m->id);
        printf("Nome: %s\n", d->nome);
        printf("Matricula: %d\n", d->numero_matricula);
        printf("Nota Teorica: %.2f\n", m->nota_teorica);
        printf("Nota Pratica: %.2f\n", m->nota_pratica);
        printf("Faltas: %d\n", m->aulas_ausente);


        printf("\n");
    }
}