#include "view/relatorio_view.h"
#include "model/turma.h"
#include "model/matricula.h"
#include "model/discente.h"
#include "model/docente.h"
#include "model/disciplina.h"
#include "dao/turmaDAO.h"
#include "dao/matriculaDAO.h"
#include "dao/discenteDAO.h"
#include "dao/docenteDAO.h"
#include "dao/disciplinaDAO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exibir_relatorio_turma(int id_turma) {
    Turma *turma = buscar_turma(id_turma);
    if (!turma) {
        printf("Turma não encontrada.\n");
        return;
    }

    Disciplina *disciplina = buscar_disciplina(turma->id_disciplina);
    if (!disciplina) {
        printf("Disciplina não encontrada.\n");
        return;
    }

    Docente *docente = buscar_docente(turma->docente_id);
    if (!docente) {
        printf("Docente não encontrado.\n");
        return;
    }

    DAO_list matriculas = buscar_matriculas_por_turma(id_turma);

    // Calcular estatísticas
    float media_geral = 0.0;
    int total_alunos = matriculas.size;
    int total_evasoes = 0;
    int tem_defasagem = 0;
    float grau_defasagem = 0.0;
    int todos_aprovados = 1;

    // Lista para alunos
    typedef struct {
        char nome[128];
        float media;
        char status[20];
        int is_evadido;
    } AlunoInfo;

    AlunoInfo *alunos = malloc(total_alunos * sizeof(AlunoInfo));
    int count = 0;

    for (int i = 0; i < matriculas.size; i++) {
        Matricula *m = (Matricula*)matriculas.items[i];
        Discente *d = buscar_discente(m->discente_id);
        if (!d) continue;

        float media_aluno = (m->nota_teorica + m->nota_pratica) / 2.0;
        media_geral += media_aluno;
        grau_defasagem += m->tempo_ausente;

        strcpy(alunos[count].nome, d->nome);
        alunos[count].media = media_aluno;

        if (m->tem_evasao) {
            strcpy(alunos[count].status, "Evadido");
            alunos[count].is_evadido = 1;
            total_evasoes++;
        } else {
            if (media_aluno >= 7.0) {
                strcpy(alunos[count].status, "Aprovado");
            } else {
                strcpy(alunos[count].status, "Reprovado");
                todos_aprovados = 0;
            }
            alunos[count].is_evadido = 0;
        }

        if (m->tempo_ausente > 20) {
            tem_defasagem = 1;
        }

        count++;
    }

    if (total_alunos > 0) {
        media_geral /= total_alunos;
        grau_defasagem /= total_alunos;
    }

    char status_turma[50];
    if (media_geral > 7.0 && todos_aprovados) {
        strcpy(status_turma, "Turma Destaque");
    } else {
        strcpy(status_turma, "Turma com Problemas");
    }

    // Cabeçalho
    printf("=== Relatório Detalhado da Turma ===\n");
    printf("Código da Turma: %s\n", turma->codigo);
    printf("Nome da Disciplina: %s\n", disciplina->nome);
    printf("Nome do Docente: %s\n", docente->nome);
    printf("Grau de Defasagem: %.2f horas\n", grau_defasagem);

    // Estatísticas
    printf("\nEstatísticas:\n");
    printf("Média Geral: %.2f\n", media_geral);
    printf("Total de Alunos: %d\n", total_alunos);
    printf("Total de Evasões: %d\n", total_evasoes);

    // Status de Defasagem
    printf("\nStatus de Defasagem: ");
    if (tem_defasagem) {
        printf("Turma com Defasagem\n");
    } else {
        printf("Turma sem Defasagem\n");
    }

    printf("Status da Turma: %s\n", status_turma);

    // Lista de Alunos - ordenar por média decrescente, destaque no topo
    // Simples bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (alunos[j].media < alunos[j+1].media) {
                AlunoInfo temp = alunos[j];
                alunos[j] = alunos[j+1];
                alunos[j+1] = temp;
            }
        }
    }

    printf("\nLista de Alunos:\n");
    printf("%-30s %-10s %-15s\n", "Nome", "Média", "Status");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-30s %-10.2f %-15s\n", alunos[i].nome, alunos[i].media, alunos[i].status);
    }

    // Liberar memória
    free(alunos);
    // Liberar matriculas.items? Assumir que não, pois são ponteiros para os mesmos objetos.

    // Liberar turma, etc? Assumir que buscar_ retorna alocados, mas não liberar aqui.
}