#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "view/menu_turma.h"
#include "view/relatorio_view.h"

#include "utils/utils.h"
#include "model/turma.h"
#include "model/discente.h"
#include "model/disciplina.h"
#include "model/matricula.h"

#include "controller/notas_controller.h"
#include "controller/diagnostico_controller.h"
#include "controller/turma_controller.h"
#include "controller/matricula_controller.h"
#include "controller/discente_controller.h"

#include "dao/discenteDAO.h"
#include "dao/disciplinaDAO.h"
#include "dao/turmaDAO.h"

static Turma *buscar_turma_na_lista(DAO_list *lista, int id_turma) {
    for (int i = 0; i < lista->size; i++) {
        Turma *t = lista->items[i];
        if (!t) continue;
        if (t->id == id_turma) {
            return t;
        }
    }
    return NULL;
}

static float calcular_media_matricula(Matricula *m) {
    if (!m) return -1.0f;
    float soma = 0.0f;
    int qtd = 0;

    if (m->nota_teorica >= 0) {
        soma += m->nota_teorica;
        qtd++;
    }
    if (m->nota_pratica >= 0) {
        soma += m->nota_pratica;
        qtd++;
    }

    if (qtd == 0) {
        return -1.0f;
    }

    return soma / qtd;
}

static void listar_discentes_sistema(void) {
    DAO_list lista = listar_discentes();

    if (lista.size == 0 || !lista.items) {
        puts("Nenhum discente cadastrado no sistema.");
        if (lista.items) free(lista.items);
        return;
    }

    puts("\n| ID Discente | Nome");
    puts("----------------------------------------------");

    for (int i = 0; i < lista.size; i++) {
        Discente *d = lista.items[i];
        if (!d) continue;
        printf("| %-10d | %s\n", d->id, d->nome);
    }

    free(lista.items);
}

static void mostrar_ranking_turma(int id_turma) {
    DAO_list matriculas = listar_matriculas_turma(id_turma);

    if (matriculas.size == 0 || !matriculas.items) {
        puts("Nenhuma matricula encontrada para esta turma.");
        if (matriculas.items) free(matriculas.items);
        return;
    }

    typedef struct {
        int id_matricula;
        int id_discente;
        char nome[256];
        float media;
        bool tem_evasao;
    } RankingAluno;

    RankingAluno *ranking = malloc(sizeof(RankingAluno) * matriculas.size);
    int count = 0;

    for (int i = 0; i < matriculas.size; i++) {
        Matricula *m = matriculas.items[i];
        if (!m) continue;

        float media = calcular_media_matricula(m);
        if (media < 0) {
            continue;
        }

        Discente *d = buscar_discente(m->discente_id);
        if (!d) continue;

        ranking[count].id_matricula = m->id;
        ranking[count].id_discente = m->discente_id;
        strncpy(ranking[count].nome, d->nome, sizeof(ranking[count].nome) - 1);
        ranking[count].nome[sizeof(ranking[count].nome) - 1] = '\0';
        ranking[count].media = media;
        ranking[count].tem_evasao = m->tem_evasao;
        count++;
    }

    if (count == 0) {
        puts("Nenhum aluno com notas registradas para ranking.");
        free(ranking);
        free(matriculas.items);
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (ranking[j].media < ranking[j + 1].media) {
                RankingAluno temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    puts("\n=== Aluno destaque ===");
    printf("%s - Media: %.2f\n", ranking[0].nome, ranking[0].media);
    puts("\nRanking de alunos da turma:");
    printf("%-5s %-30s %-8s %-12s\n", "ID", "Nome", "Media", "Status");
    puts("------------------------------------------------------------------");

    for (int i = 0; i < count; i++) {
        const char *status = ranking[i].tem_evasao ? "Evadido" : "Ativo";
        printf("%-5d %-30s %-8.2f %-12s\n", ranking[i].id_discente, ranking[i].nome, ranking[i].media, status);
    }

    free(ranking);
    free(matriculas.items);
}

static void mostrar_alerta_defasagem(int id_turma) {
    DiagnosticoTurma d = calcularDiagnosticoTurma(id_turma);

    if (d.totalAlunos == 0) {
        puts("Nenhum dado de matricula encontrado para esta turma.");
        return;
    }

    puts("\n=== Alerta de Defasagem ===");
    printf("Total de alunos: %d\n", d.totalAlunos);
    printf("Defasagem total: %.2f horas\n", d.defasagemTotal);
    printf("Taxa de evasao: %.2f%%\n", d.taxaEvasao);
    printf("Status: %s\n", d.status);
}

static void cadastrar_matricula_na_turma(int id_turma) {
    printf("Digite o ID do discente para matricular: ");
    int id_discente = lerInteiro();

    Discente *discente = buscar_discente(id_discente);
    if (!discente) {
        puts("Discente nao encontrado.");
        return;
    }

    int resultado = realizar_matricula(id_discente, id_turma);
    if (resultado == 0) {
        puts("Matricula realizada com sucesso.");
    } else {
        puts("Erro ao matricular. Verifique se a turma e o discente sao validos ou ja estao matriculados.");
    }
}

static void excluir_matricula_turma(int id_turma) {
    DAO_list lista = listar_matriculas_turma(id_turma);
    if (lista.size == 0 || !lista.items) {
        puts("Nenhuma matricula encontrada para esta turma.");
        if (lista.items) free(lista.items);
        return;
    }

    puts("\nMatriculas da turma:");
    printf("%-5s %-10s %-30s %-12s\n", "ID", "ID Disc.", "Nome", "Status");
    puts("------------------------------------------------------------------");

    for (int i = 0; i < lista.size; i++) {
        Matricula *m = lista.items[i];
        if (!m) continue;

        Discente *d = buscar_discente(m->discente_id);
        const char *nome = d ? d->nome : "DESCONHECIDO";
        printf("%-5d %-10d %-30s %-12s\n", m->id, m->discente_id, nome, m->tem_evasao ? "Evadido" : "Ativo");
    }

    printf("\nDigite o ID da matricula para excluir: ");
    int id_matricula = lerInteiro();

    int resultado = remover_matricula(id_matricula);
    if (resultado == 0) {
        puts("Matricula excluida com sucesso.");
    } else {
        puts("Erro ao excluir matricula. Verifique o ID informado.");
    }

    free(lista.items);
}

void menu_turma(void) {
    puts("\n=== Menu de Turmas e Matriculas ===");
    printf("Digite o ID do docente logado: ");
    int id_docente = lerInteiro();

    DAO_list turmas = listar_turmas_professor(id_docente);
    if (turmas.size == 0 || !turmas.items) {
        puts("Nenhuma turma encontrada para o docente logado.");
        if (turmas.items) free(turmas.items);
        return;
    }

    puts("\nTurmas do docente:");
    printf("%-5s %-10s %-20s %-30s\n", "ID", "Codigo", "Disciplina", "Status");
    puts("-------------------------------------------------------------------------------");

    for (int i = 0; i < turmas.size; i++) {
        Turma *t = turmas.items[i];
        if (!t) continue;
        Disciplina *disciplina = buscar_disciplina(t->id_disciplina);
        const char *nome_disciplina = disciplina ? disciplina->nome : "DESCONHECIDO";
        printf("%-5d %-10s %-20s %-30s\n", t->id, t->codigo, nome_disciplina, "");
    }

    printf("\nDigite o ID da turma: ");
    int id_turma = lerInteiro();

    Turma *turma = buscar_turma_na_lista(&turmas, id_turma);
    if (!turma) {
        puts("Turma invalida. Retornando ao menu principal.");
        free(turmas.items);
        return;
    }

    int opcao = -1;
    while (opcao != 0) {
        puts("\nOpcoes:");
        puts("1. Ver Diagnostico Geral");
        puts("2. Ver Ranking de Alunos");
        puts("3. Alerta de Defasagem");
        puts("4. Excluir turma");
        puts("5. Listar todos os discentes do sistema");
        puts("6. Cadastrar matricula na turma");
        puts("7. Excluir matricula da turma");
        puts("0. Voltar");
        printf("Escolha uma opcao: ");
        opcao = lerInteiro();

        switch (opcao) {
            case 1:
                limparTela();
                exibir_relatorio_turma(id_turma);
                break;
            case 2:
                limparTela();
                mostrar_ranking_turma(id_turma);
                break;
            case 3:
                limparTela();
                mostrar_alerta_defasagem(id_turma);
                break;
            case 4:
                limparTela();
                if (excluir_turma_seguro(id_turma) == 0) {
                    puts("Turma excluida com sucesso.");
                    opcao = 0;
                } else {
                    puts("Nao foi possivel excluir a turma. Verifique se ela nao possui matriculas ativas.");
                }
                break;
            case 5:
                limparTela();
                listar_discentes_sistema();
                break;
            case 6:
                limparTela();
                cadastrar_matricula_na_turma(id_turma);
                break;
            case 7:
                limparTela();
                excluir_matricula_turma(id_turma);
                break;
            case 0:
                break;
            default:
                puts("Opcao invalida.");
                break;
        }

        if (opcao != 0) {
            puts("\nDigite enter para continuar...");
            char buffer[2];
            fgets(buffer, sizeof(buffer), stdin);
        }
    }

    free(turmas.items);
}
