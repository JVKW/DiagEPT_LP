#include <stdio.h>
#include <string.h>
#include "controller/evasao_controller.h"
#include "utils/utils.h"
#include "model/evasao.h"
#include "dao/matriculaDAO.h"
#include "dao/evasaoDAO.h"
#include "view/evasao_view.h"

void registrarEvasao(Estado *e) {
    registrarEvasaoView();
    e->alunosEvadidos++;
}

int processar_evasao_discente(int id_matricula, char *motivo) {
    // Verificar Matricula
    Matricula *m = buscar_matricula(id_matricula);
    if (m == NULL) {
        return -1;  // Erro: matricula não encontrada
    }
    if (m->tem_evasao) {
        return -1;  // Erro: matricula já marcada como evadida
    }

    // Criar Evasão
    Evasao nova_ev;
    strcpy(nova_ev.motivo, motivo);
    salvar_evasao(&nova_ev);  // Gera ID automaticamente

    // Atualizar Matricula (buscar novamente para garantir consistência)
    m = buscar_matricula(id_matricula);
    if (m == NULL) {
        return -1;  // Erro: matricula não encontrada (caso tenha sido removida entre as buscas)
    }
    m->tem_evasao = true;
    m->id_evasao = nova_ev.id;
    strcpy(m->status, "EVADIDO");

    // Persistir
    update_matricula(m);

    return 0;  // Sucesso
}    
    