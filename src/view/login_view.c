#include <stdio.h>
#include <string.h>

#include "utils/utils.h"
#include "dao/docenteDAO.h"
#include "controller/docente_controller.h"
#include "view/login_view.h"

int tela_logar_docente(){
    int logado = -1;
    DAO_list lista = buscar_docentes();
    int existe_docente = -1;
    if (lista.size > 0)
    {

        while (logado != 0 || logado != -2){
            char login[256];
            char senha[128];
            puts("\nInforme seu login:");
            lerString(login, 256);
            

            puts("\nInforme seu senha:");
            lerString(senha, 128);
            limparTela();

            int id_discent = logar_docente(login, senha);
            Docente * docent_temp = buscar_docente(id_discent);

            if (docent_temp == NULL)
            {
                existe_docente = 0;
            }

            if (strcmp(docent_temp->login, login) == 0)
            {
                existe_docente = 1;
            }
            
            
            if(existe_docente == 1){
                return id_discent;
            }else{
                limparTela();
                puts("\nDados incorretos!\n");

                int opcao = -1;
                while (opcao != 1 && opcao != 2)
                {
                    puts("1.Tentar novamente\n2.Sair");
                    opcao = lerInteiro();
                    if(opcao == 2){
                        logado = -2;
                        return -2;
                    }
                }
            }
        }
    }

    return tela_cadastrar_docente();
}

int tela_cadastrar_docente(){
    int logado = -1;
    
    Docente d;
    puts("\n=== Registro de docente ===\n");
    puts("\nInforme seu nome:");
    lerString(d.nome, 256);

    puts("\nInforme seu login:");
    lerString(d.login, 256);
    

    puts("\nInforme seu senha:");
    lerString(d.senha, 128);

    
    cadastrar_docente(&d);
    return  logar_docente(d.login, d.senha);

}