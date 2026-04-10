#include <stdio.h>
#include <string.h>
#include "controller/evasao_controller.h"
#include "utils/utils.h"
#include "model/evasao.h"
#include "dao/matriculaDAO.h"
#include "dao/evasaoDAO.h"

void registrarEvasao(Estado *e) {
    char motivo[300];

    printf("Motivo da Evasao: ");
    lerString(motivo, 300);

    e->alunosEvadidos++;

    printf("Evasao Registrada: %s\n", motivo);
}

int processar_evasao_discente(int id_matricula, char *motivo) {
    // Verificar Matrícula
    Matricula *m = buscar_matricula(id_matricula);
    if (m == NULL) {
        return -1;  // Erro: matrícula não encontrada
    }

    // Criar Evasão
    Evasao nova_ev;
    strcpy(nova_ev.motivo, motivo);
    salvar_evasao(&nova_ev);  // Gera ID automaticamente

    // Atualizar Matrícula (buscar novamente para garantir consistência)
    m = buscar_matricula(id_matricula);
    if (m == NULL) {
        return -1;  // Erro: matrícula não encontrada (caso tenha sido removida entre as buscas)
    }
    m->tem_evasao = true;
    m->id_evasao = nova_ev.id;
    strcpy(m->status, "EVADIDO");

    // Persistir
    update_matricula(m);

    return 0;  // Sucesso
}    
    