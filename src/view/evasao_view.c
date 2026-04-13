#include <stdio.h>
#include <string.h>
#include "utils/utils.h"
#include "controller/evasao_controller.h"
#include "dao/matriculaDAO.h"
#include "dao/discenteDAO.h"
#include "dao/evasaoDAO.h"
#include "model/lista_generica.h"

void registrarEvasaoView() {
    // Listar alunos e matriculas
    printf("=== LISTA DE ALUNOS E MATRICULAS ===\n");
    DAO_list matriculas = buscar_matriculas();
    for (int i = 0; i < matriculas.size; i++) {
        Matricula *m = (Matricula *)matriculas.items[i];
        Discente *d = buscar_discente(m->discente_id);
        if (d != NULL) {
            printf("ID Matricula: %d - Nome: %s\n", m->id, d->nome);
        }
    }
    // Liberar memória se necessário, mas assumindo que DAO_list cuida disso

    // Inputs
    printf("ID da Matricula do aluno evadido: ");
    int id_matricula = lerInteiro();

    char motivo[2048];
    printf("Motivo da evasao: ");
    lerString(motivo, 2048);

    // Execução
    int resultado = processar_evasao_discente(id_matricula, motivo);
    if (resultado == 0) {
        printf("Evasao registrada com sucesso!\n");
    } else {
        printf("Erro ao registrar evasao. Verifique o ID da matricula.\n");
    }
}


void relatorio_evasoes(){
    DAO_list matriculas = buscar_matriculas();
    bool evasao_flag = false;
    
    for(int i; i < matriculas.size; i++){
        
        Matricula * aux = matriculas.items[i];
        if (aux->tem_evasao == true)
        {
            Discente * aluno = buscar_discente(aux->discente_id);
            if (aluno == NULL)
            {
                continue;
            }
            
            if (i == 0)
            {
                puts("| ID Discente |                   Nome                 |       Motivo");
            }
            Evasao * evasao = buscar_evasao(aux->id_evasao);
            if (strcmp(evasao->motivo, "") == 0)
            {
                printf("   %010d |  %30s        |   ?????????", aluno->id, aluno->nome);
            }else{
                printf("   %010d |  %30s        |   %s", aluno->id, aluno->nome, evasao->motivo);
            }

            evasao_flag = true;
        }
    }
    puts(evasao_flag == false ? "Não há evasoes registradas ate o momento": "");
}