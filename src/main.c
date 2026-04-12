#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model/lista_generica.h"

#include "controller/docente_controller.h"
#include "controller/curso_controller.h"
#include "controller/disciplina_controller.h"
#include "controller/turma_controller.h"
#include "controller/diagnostico_controller.h"

#include "controller/discente_controller.h"
#include "controller/matricula_controller.h"

#include "utils/utils.h"
#include "controller/evasao_controller.h"
#include "utils/utils.h"
#include "dao/discenteDAO.h"

#include "view/discente_view.h"

#include "dao/jsonDAO.h"

#include "view/curso_view.h"
#include "view/relatorio_view.h"
#include "view/relatorio_evasao_view.h"

// Quando o usuário estiver logado deve ter o valor 1
// Quando o usuário estiver deslogado deve ter o valor 0
int USUARIO_AUTENTICADO = 0; 


// PADÃO DE CÓDIGOS DE ERRO
/*
     0 Executou sem erros;
    -1 Erro na valição;
*/

void imprimir_menu(){
        char * texto_menu = {"1.Gestao de Cursos\n2.Gestao de Disciplinas\n3.Gestao de Turmas e Matriculas\n4.Gestao de discentes\n5.Lancamento de Notas\n6.Relatorios e Diagnosticos\n7.Registro de Evasoes\n8.Sair\n"};
        printf("%s",texto_menu);
    }

int main() {

    
    
    /*
    1.Gestao de Cursos (view/curso_view.h)
    tela_cadastrar_curso();
    tela_excluir_curso();
    2.Gestão de Disciplinas (src/view/disciplina_view.h)
    Validação de carga horária e codigos únicos.
    3.Gestão de Turmas e Matrículas (view/menu_turma.h)
    Listagem de turmas do docente, busca de discentes e controle de matrículas.
    4.Gestão de discentes (view/discente_view.h)
    menu_registrar_aluno()
    não menu_remover_aluno()
    5.Lançamento de Notas (view/notas_view.h)
    Fluxo de seleção de turma e loop de entrada de notas.
    6.Relatórios e Diagnósticos (view/relatorio_view.h)
    Dashboard da turma, ranking de alunos e estatísticas.
    7.Registro de Evasões (view/evasao_view.h)
    Captura de motivos e atualização de status.
    8.Sair

    */

    int opcao = -1;
    int opcao_sub = -1;
   do{
        opcao = -1;
        opcao_sub = -1;    
        
        logoPrint();

        imprimir_menu();
        opcao = lerInteiro();
        switch (opcao)
        {
        case 1:
            limparTela();
            while(opcao_sub != 3){
                puts(" 1.Registrar curso\n 2.Remover curso\n 3.Sair");
                opcao_sub = lerInteiro();
                switch (opcao_sub)
                {
                case 1:
                    tela_cadastrar_curso();
                    break;
                case 2:
                
                    tela_excluir_curso();
                    break;
                case 3:
                    opcao_sub = 3;
                    
                    limparTela();
                    break;
                
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;
        case 2:
        
            break;
        
        default:
            puts("Opcao invalida!");
            break;
        }
    
        limparTela();
    }while(opcao != 8);


    return 0;
}