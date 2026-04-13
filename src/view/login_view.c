#include <stdio.h>
#include <string.h>

#include "utils/utils.h"
#include "dao/docenteDAO.h"
#include "controller/docente_controller.h"

int tela_logar_docente(){
    int logado = -1;
    DAO_list * lista = buscar_docentes;
    if (lista == NULL || lista->size == 0)
    {
        Docente d;
        puts("\n=== Registro de docente ===\n");
        puts("\n Informe seu nome:");
        lerString(d.nome, 256);

        puts("\n Informe seu login:");
        lerString(d.login, 256);
        

        puts("\n Informe seu senha:");
        lerString(d.senha, 128);

        
        cadastrar_docente(&d);

        return 1;
    }
    
    while (logado != 0 || logado != -2)
    {
        char * login, senha;
        puts("\n Informe seu login:");
        lerString(login, 256);
        

        puts("\n Informe seu senha:");
        lerString(senha, 128);

        int logado = logar_docente(login, senha);
        if(logado == 0){
            return 1;
        }else{
            limparTela();
            puts("/n Dados incorretos!\n\n");

            int opcao = -1;
            while (opcao != 1 && opcao != 2)
            {
                puts("\n1.Tentar novamente\n2.Sair");
                opcao = lerInteiro();
                if(opcao == 2){
                    logado = -2;
                    return 0;
                }
            }
        }
    }
}