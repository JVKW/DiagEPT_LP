#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "controller/curso_controller.h"
#include "controller/diagnostico_controller.h"
#include "controller/discente_controller.h"
#include "controller/disciplina_controller.h"
#include "controller/docente_controller.h"
#include "controller/evasao_controller.h"
#include "controller/matricula_controller.h"
#include "controller/notas_controller.h"
#include "controller/ranking_controller.h"
#include "controller/turma_controller.h"

#include "dao/matriculaDAO.h"
#include "model/estado.h"

static int obter_valor_unico(void) {
    static int contador = 1;
    return (int)(time(NULL) % 100000) + contador++;
}

static void separador(const char *titulo) {
    printf("\n========================================\n");
    printf(" %s\n", titulo);
    printf("========================================\n");
}

static void teste_docente_controller(Docente *docente_saida) {
    separador("TESTE DOCENTE CONTROLLER");

    Docente docente = {0};
    sprintf(docente.nome, "Docente Teste %d", obter_valor_unico());
    sprintf(docente.login, "login_teste_%d", obter_valor_unico());
    sprintf(docente.senha, "senhaTeste123");

    int resultado = cadastrar_docente(&docente);
    printf("cadastrar_docente => %d\n", resultado);
    if (resultado != 0) {
        printf("Erro ao cadastrar docente. Login possivelmente existente.\n");
    }

    int login = logar_docente(docente.login, docente.senha);
    printf("logar_docente => %d\n", login);

    Docente buscado = buscar_docente_id(docente.id);
    printf("buscar_docente_id => id %d, nome %s, login %s\n",
           buscado.id,
           buscado.nome,
           buscado.login);

    *docente_saida = docente;
}

static int teste_curso_controller(void) {
    separador("TESTE CURSO CONTROLLER");

    Curso curso = {0};
    curso.carga_horaria_total = 120;
    sprintf(curso.codigo, "CURSO_TST_%d", obter_valor_unico());
    sprintf(curso.nome, "Curso Teste %d", obter_valor_unico());
    curso.id_disciplinas = NULL;
    curso.qtd_disciplinas = 0;

    int resultado = cadastrar_curso(&curso);
    printf("cadastrar_curso => %d\n", resultado);
    printf("curso salvo id => %d\n", curso.id);

    if (resultado != 0) {
        printf("Falha ao cadastrar curso.\n");
    }

    return curso.id;
}

static int teste_disciplina_controller(int curso_id) {
    separador("TESTE DISCIPLINA CONTROLLER");

    Disciplina disciplina = {0};
    strcpy(disciplina.nome, "Disciplina Teste");
    sprintf(disciplina.codigo, "DISC_TST_%d", obter_valor_unico());
    disciplina.carga_horaria_total = 60;
    disciplina.id_turma = NULL;
    disciplina.qtd_turma = 0;

    int resultado = cadastrar_disciplina(&disciplina, curso_id);
    printf("cadastrar_disciplina => %d\n", resultado);
    printf("disciplina salva id => %d\n", disciplina.id);

    return disciplina.id;
}

static Discente teste_discente_controller(void) {
    separador("TESTE DISCENTE CONTROLLER");

    Discente discente = {0};
    discente.numero_matricula = obter_valor_unico();
    sprintf(discente.nome, "Discente Teste %d", discente.numero_matricula);

    int resultado = cadastrar_discente(&discente);
    printf("cadastrar_discente => %d\n", resultado);

    Discente buscado = buscar_discente_id(discente.id);
    printf("buscar_discente_id => id %d, nome %s, matricula %d\n",
           buscado.id,
           buscado.nome,
           buscado.numero_matricula);

    strcpy(buscado.nome, "Discente Atualizado");
    update_discente_id(&buscado);
    printf("update_discente_id => nome atualizado para %s\n", buscado.nome);

    return buscado;
}

static void atualizar_notas_matricula(Matricula *m, float teorica, float pratica, int aulas_ausente) {
    if (!m) return;
    m->nota_teorica = teorica;
    m->nota_pratica = pratica;
    m->aulas_ausente = aulas_ausente;
    update_matricula(m);
}

static void testar_notas_ranking_diagnostico(int id_turma, int id_docente) {
    separador("TESTE NOTAS, RANKING E DIAGNOSTICO");

    DAO_list turmas = listar_turmas_professor(id_docente);
    printf("listar_turmas_professor => %d turmas encontradas\n", turmas.size);
    for (int i = 0; i < turmas.size; i++) {
        Turma *t = turmas.items[i];
        printf("  turma id=%d disciplina=%d docente=%d\n",
               t->id,
               t->id_disciplina,
               t->docente_id);
    }

    DAO_list mats = listar_matriculas_turma(id_turma);
    printf("listar_matriculas_turma => %d matriculas encontradas\n", mats.size);
    for (int i = 0; i < mats.size; i++) {
        Matricula *m = mats.items[i];
        const char *nome = obter_nome_discente_por_matricula(m);
        printf("  matricula id=%d discente=%s media=%.2f status=%s\n",
               m->id,
               nome,
               calcularMediaAluno(m),
               m->status);
    }

    if (mats.size > 0) {
        Matricula *destaque = obterAlunoDestaque(id_turma);
        if (destaque) {
            printf("obterAlunoDestaque => id=%d media=%.2f\n",
                   destaque->id,
                   calcularMediaAluno(destaque));
        } else {
            printf("obterAlunoDestaque => nenhum destaque\n");
        }
    }

    DAO_list ranking = obterRankingMatriculas(id_turma);
    printf("obterRankingMatriculas => %d registros\n", ranking.size);
    for (int i = 0; i < ranking.size; i++) {
        Matricula *m = ranking.items[i];
        printf("  ranking pos=%d id=%d media=%.2f\n",
               i + 1,
               m->id,
               calcularMediaAluno(m));
    }
    free(ranking.items);

    DiagnosticoTurma diagnostico = calcularDiagnosticoTurma(id_turma);
    printf("calcularDiagnosticoTurma => totalAlunos=%d taxaEvasao=%.2f%% mediaGeral=%.2f status=%s\n",
           diagnostico.totalAlunos,
           diagnostico.taxaEvasao,
           diagnostico.mediaGeral,
           diagnostico.status);

    printf("turmaEhDestaque => %s\n",
           turmaEhDestaque(id_turma) ? "true" : "false");

    free(mats.items);
    free(turmas.items);
}

int main(void) {
    srand((unsigned) time(NULL));

    Docente docente = {0};
    teste_docente_controller(&docente);

    int curso_id = teste_curso_controller();
    int disciplina_id = teste_disciplina_controller(curso_id);

    separador("TESTE TURMA CONTROLLER");
    int turma_id = criar_turma(disciplina_id, docente.id);
    printf("criar_turma => %d\n", turma_id);

    Discente discente1 = teste_discente_controller();
    Discente discente2 = teste_discente_controller();

    separador("TESTE MATRICULA CONTROLLER");
    int resultado1 = realizar_matricula(discente1.id, turma_id);
    int resultado2 = realizar_matricula(discente2.id, turma_id);
    printf("realizar_matricula discente1 => %d\n", resultado1);
    printf("realizar_matricula discente2 => %d\n", resultado2);

    DAO_list matriculas = listar_matriculas_turma(turma_id);
    for (int i = 0; i < matriculas.size; i++) {
        Matricula *m = matriculas.items[i];
        if (i == 0) {
            atualizar_notas_matricula(m, 8.5f, 9.0f, 1);
        } else {
            atualizar_notas_matricula(m, 6.0f, 7.0f, 2);
        }
    }
    free(matriculas.items);

    testar_notas_ranking_diagnostico(turma_id, docente.id);

    separador("TESTE EVASAO CONTROLLER");
    matriculas = listar_matriculas_turma(turma_id);
    if (matriculas.size > 0) {
        Matricula *mat1 = (Matricula *)matriculas.items[0];
        int id_matricula = mat1->id;
        int evasao_result = processar_evasao_discente(id_matricula, "Frequencia insuficiente");
        printf("processar_evasao_discente => %d\n", evasao_result);

        Estado estado = {0};
        inicializarEstado(&estado);
        registrarEvasao(&estado);
        printf("registrarEvasao => alunosEvadidos=%d\n", estado.alunosEvadidos);
    }
    free(matriculas.items);

    separador("TESTE REMOCAO DE MATRICULA");
    matriculas = listar_matriculas_turma(turma_id);
    if (matriculas.size > 1) {
        Matricula *mat2 = (Matricula *)matriculas.items[1];
        int id_matricula_remover = mat2->id;
        int remover_result = remover_matricula(id_matricula_remover);
        printf("remover_matricula => %d\n", remover_result);
    }
    free(matriculas.items);

    separador("TESTE EXCLUSAO TURMA SEGURO");
    int turma_temp = criar_turma(disciplina_id, docente.id);
    printf("criar turma temporaria => %d\n", turma_temp);
    int excluir_turma = excluir_turma_seguro(turma_temp);
    printf("excluir_turma_seguro => %d\n", excluir_turma);

    separador("TESTE REMOCAO DISCIPLINA SEGURO");
    int curso_temp = teste_curso_controller();
    int disciplina_temp = teste_disciplina_controller(curso_temp);
    int remover_disciplina = remover_disciplina_seguro(disciplina_temp);
    printf("remover_disciplina_seguro => %d\n", remover_disciplina);

    separador("TESTE REMOCAO CURSO SEGURO");
    int remover_curso = remover_curso_seguro(curso_temp);
    printf("remover_curso_seguro => %d\n", remover_curso);

    printf("\nTeste completo finalizado.\n");
    return 0;
}

// Testa controladores
// gcc teste_total.c src/controller/*.c src/dao/*.c src/model/*.c src/utils/*.c src/json_mapper/*.c src/view/*.c lib/cjson/cJSON.c -Iinclude -Iinclude/cjson -Wall -Wextra -g -o teste.exe