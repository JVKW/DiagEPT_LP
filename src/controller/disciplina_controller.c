#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "controller/disciplina_controller.h"
#include "controller/curso_controller.h"
#include "dao/disciplinaDAO.h"
#include "model/lista_generica.h"
#include "model/disciplina.h"


/*
    CÓDIGOS DE RETORNO:
     0 SUCESSO
    -1 ERRO INFORMAÇÕES INCORRETAS
    -2 ERRO AO REALIZAR A OPERAÇÃO

*/
int cadastrar_disciplina(Disciplina *d, int id_disciplina){
    d->id = dao_next_id(DISCIPLINA_FILE);
    d->qtd_turma = 0;
    d->id_turma  = NULL; 

    DAO_list lista = buscar_disciplinas();

    if (d->carga_horaria_total <=0)
    {
        return -1;
    }
     
    for(int i = 0; i < lista.size; i++){
        Disciplina * temp = lista.items[i];
        if (strcmp(temp->codigo, d->codigo) == 0)
        {
            return -2;
        }
    }

    int result = adicionar_disciplina(id_disciplina, d->id);
    if (result != 0)
    {
        return result;
    }

    salvar_disciplina(d);

    return 0;
}

int remover_disciplina_seguro(int id){
    if (existe_disciplina(id) != 0){
        return -2;
    }

    Disciplina * temp = buscar_disciplina(id);
    if (temp->qtd_turma >= 1){
        return -2;        
    }
    
    excluir_disciplina(id);

    return 0;
}

Disciplina buscar_disciplina_id(int id) {
    Disciplina *d = buscar_disciplina(id);
    if (!d) {
        Disciplina vazio = {0};
        return vazio;
    }
    return *d;
}

void adicionar_turma_na_disciplina(int id_disciplina, int nova_turma_id) {
    Disciplina * disc = buscar_disciplina(id_disciplina);

    int novo_tamanho = disc->qtd_turma + 1;
    
    int *turmas_atuais = malloc(sizeof(int) * novo_tamanho);

    for (int i = 0; i < disc->qtd_turma; i++){
        turmas_atuais[i] = disc->id_turma[i];
    }

    free(disc->id_turma);

    disc->id_turma = turmas_atuais;
    disc->id_turma[disc->qtd_turma] = nova_turma_id;
    disc->qtd_turma = novo_tamanho;

    atualizar_disciplina(disc);
}

int remover_turma_na_disciplina(int id_disciplina, int turma_id){
    if (existe_disciplina(id_disciplina) != 0){
        return -1;
    }
    

    Disciplina * disc = buscar_disciplina(id_disciplina);

    int novo_tamanho = disc->qtd_turma - 1;
    
    int *turmas_atuais = malloc(sizeof(int) * novo_tamanho);

    int pos = -1;


    for (int i = 0; i < novo_tamanho+1; i++) {
        turmas_atuais[i] = disc->id_turma[i];
        if (turmas_atuais[i] == turma_id) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        for (int i = pos; i < novo_tamanho; i++) {
            turmas_atuais[i] = disc->id_turma[i + 1];
        }
    }else{
        return -1;
    }

    free(disc->id_turma);

    disc->id_turma = turmas_atuais;
    disc->qtd_turma = novo_tamanho;

    atualizar_disciplina(disc);

    return 0;
}