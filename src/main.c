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
#include "controller/evasao_controller.h"

#include "utils/utils.h"

#include "dao/discenteDAO.h"
#include "dao/evasaoDAO.h"
#include "dao/jsonDAO.h"

#include "view/discente_view.h"
#include "view/curso_view.h"
#include "view/disciplina_view.h"
#include "view/relatorio_view.h"
#include "view/evasao_view.h"
#include "view/turma_view.h"
#include "view/menu_turma.h"
#include "view/login_view.h"
#include "view/notas_view.h"

// Quando o usuário estiver logado deve ter o id do docente
// Quando o usuário estiver deslogado deve ter um valor negativo e encerra o programa

int USUARIO_AUTENTICADO; 

// PADRÃO DE CÓDIGOS DE ERRO
/*
     0 Executou sem erros;
    -1 Erro na valição;
*/

void imprimir_menu(){
        char * texto_menu = {"1. Gestao de Cursos\n2. Gestao de Disciplinas\n3. Gestao de Turmas e Matriculas\n4. Gestao de discentes\n5. Lancamento de Notas\n6. Relatorios e Diagnosticos\n7. Registro de Evasoes\n8. Sair\n\n"};
        printf("%s",texto_menu);
    }

void continuar(){
    puts("\nDigite enter para continuar:");
    char aux;
    scanf("%c", &aux);
}

void tela_listar_cursos();

int main() {
    /*
    MENU DE OPÇÕES

    (OK) 1. Gestao de Cursos (view/curso_view.h)
    tela_cadastrar_curso();
    tela_excluir_curso();

    (OK) 2. Gestão de Disciplinas (src/view/disciplina_view.h)
    Validação de carga horária e codigos únicos.

    (OK) 3. Gestão de Turmas e Matriculas (view/menu_turma.h)
    Listagem de turmas do docente, busca de discentes e controle de matriculas.

    (OK) 4. Gestão de discentes (view/discente_view.h)
    menu_registrar_aluno();
    menu_remover_aluno();

    (OK)5. Lançamento de Notas (view/notas_view.h)
    Fluxo de seleção de turma e loop de entrada de notas.

    (OK) 6.Relatórios e Diagnósticos (view/relatorio_view.h)
    Dashboard da turma, ranking de alunos e estatísticas.

    (OK) 7. Registro de Evasões (view/evasao_view.h)
    Captura de motivos e atualização de status.

    (OK) 8.Sair
    */

    limparTela();
    logoPrint();
    USUARIO_AUTENTICADO = tela_logar_docente();
    if (USUARIO_AUTENTICADO < 1)
    {
    
        limparTela();
        logoPrint();
        puts("Obrigado por utilizar o DiagEPT!\n\nSaindo do sistema...");
        exit(0);
    }

    int opcao = -1;
    int opcao_sub1 = -1;
    int opcao_sub2 = -1;
    int opcao_sub3 = -1;
    int opcao_sub4 = -1;
    int opcao_sub5 = -1;
    int opcao_sub6 = -1;
    int opcao_sub7 = -1;

   do{
        opcao = -1;
        opcao_sub1 = -1;
        opcao_sub2 = -1;
        opcao_sub3 = -1;
        opcao_sub4 = -1;
        opcao_sub5 = -1;
        opcao_sub6 = -1;
        opcao_sub7 = -1;
    
        logoPrint();

        imprimir_menu();
        opcao = lerInteiro();

        switch (opcao)
        {
        case 1:
            limparTela();
            while(opcao_sub1 != 4){
                logoPrint();
                puts("1. Registrar curso\n2. Remover curso\n3. Listar cursos\n4. Sair\n");
                opcao_sub1 = lerInteiro();
                switch (opcao_sub1)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    tela_cadastrar_curso();
                    continuar();
                    break;
                case 2:
                    limparTela();
                    logoPrint();
                    tela_excluir_curso();
                    continuar();
                    break;
                case 3:
                    limparTela();
                    logoPrint();
                    tela_listar_cursos();
                    continuar();
                    break;
                case 4:
                    opcao_sub1 = 4;
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
            limparTela();
            while (opcao_sub2 != 4){
                logoPrint();
                puts("1. Registrar disciplina\n2. Remover disciplina\n3. Listar disciplina\n4. Sair\n");
                opcao_sub2 = lerInteiro();
                switch (opcao_sub2)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    menu_cadastrar_disciplina();
                    continuar();
                    break;
                case 2:
                    limparTela();
                    logoPrint();
                    menu_remover_disciplina();
                    continuar();
                    break;
                case 3:
                    limparTela();
                    logoPrint();
                    listar_todas_disciplinas();
                    continuar();
                    break;
                case 4:
                    opcao_sub2 = 4;
                    limparTela();
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;
        
        case 3:
            limparTela();
            while (opcao_sub3 != 3){
                logoPrint();
                puts("1. Criar turmas\n2. Menu turmas\n3. Sair\n");
                opcao_sub3 = lerInteiro();
                switch (opcao_sub3)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    fluxo_criar_turma();
                    continuar();
                    break;
                case 2:
                    limparTela();
                    logoPrint();
                    menu_turma(USUARIO_AUTENTICADO);
                    continuar();
                case 3:
                    opcao_sub3 = 3;
                    limparTela();
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;
        
        case 4:
            limparTela();
            while(opcao_sub4 != 4){
                logoPrint();
                puts("1. Registrar aluno\n2. Remover aluno\n3. Listar discentes\n4. Sair\n");
                opcao_sub4 = lerInteiro();
                switch (opcao_sub4)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    menu_registrar_aluno();
                    continuar();
                    break;
                case 2:
                    limparTela();
                    logoPrint();
                    menu_remover_aluno();
                    continuar();
                    break;
                case 3:
                    limparTela();
                    logoPrint();
                    listar_todas_discentes();
                    continuar();
                case 4:
                    opcao_sub4 = 4;
                    limparTela();
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;
        
        case 5:
            limparTela();
            while(opcao_sub5 != 2){
                logoPrint();
                puts("1. Gerenciar notas\n2. Sair\n");
                opcao_sub5 = lerInteiro();
                switch (opcao_sub5)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    menu_lancar_notas(USUARIO_AUTENTICADO);
                    break;
                case 2:
                    opcao_sub5 = 2;
                    limparTela();
                    break;
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;
        
        case 6:
            limparTela();
            while(opcao_sub6 != 2){
                logoPrint();
                puts("1. Dashboard da turma, ranking de alunos e estatisticas\n2. Sair\n");
                opcao_sub6 = lerInteiro();
                switch (opcao_sub6)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    printf("\nDigite o ID da turma: ");
                    int id_turma = lerInteiro();
                    exibir_relatorio_turma(id_turma);
                    continuar();
                    break;
                case 2:
                    opcao_sub6 = 2;
                    limparTela();
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;

        case 7:
            limparTela();
            while (opcao_sub7 != 3){
                logoPrint();
                puts("\n1. Captura de motivos e atualizacao de status\n2. Listar todas as evasoes\n3. Sair\n");
                opcao_sub7 = lerInteiro();
                switch (opcao_sub7)
                {
                case 1:
                    limparTela();
                    logoPrint();
                    registrarEvasaoView();
                    continuar();
                    break;
                case 2:
                    limparTela();
                    logoPrint();
                    relatorio_evasoes();
                    continuar();
                    break;
                case 3:
                    opcao_sub7 = 3;
                    limparTela();
                    break;
                default:
                    puts("Opcao invalida!");
                    break;
                }
                limparTela();
            }
            break;
        
        case 8:
            limparTela();
            logoPrint();
            puts("Obrigado por utilizar o DiagEPT!\n\nSaindo do sistema...");
            opcao = 8;
            break;

        default:
            puts("Opcao invalida!");
            break;
        }
    }while(opcao != 8);

    return 0;
}