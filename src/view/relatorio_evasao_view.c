#include <stdio.h>
#include <string.h>

#include "dao/matriculaDAO.h"
#include "dao/discenteDAO.h"
#include "dao/evasaoDAO.h"


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