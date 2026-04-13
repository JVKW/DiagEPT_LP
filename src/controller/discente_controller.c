#include <string.h>
#include <stdio.h>
#include "dao/discenteDAO.h"
#include "controller/discente_controller.h"
#include "dao/matriculaDAO.h"

int cadastrar_discente(Discente *d){
    //conversão dos arquivo json para se tornarem discentes criando a lista 
    DAO_list lista = buscar_discentes();
    //loop que começa em zero e teremina quando a lista fica do tamanho da quantia de discentes menos 1 pq encerra quando fica do mesmo tamanho somando de 1 em 1
    for (int i= 0; i < lista.size; i++ ) { 
        //aqui eu uso uma conversão de tipo CAST (discente *) (tipo (que é discente ) e valor (que é um ponteiro, hexadecimal) ou seja eu tô apontando para a lista e guardando como discente no arquivo json)

        //mas tbm da pra criar uma variavel temp so pra guardar o item da lista se quiser, nao sei se faz diferença

        //não criei a lista.items dentro do loop, so to usando

        Discente* existente = lista.items[i];
        //comparando matricula exitente com a seguinte matricula sendo esse d o discente novo que a gente ta tentando cadastrar
        // ai basicamente se o numero da matricula que ta dentro da lista ja existir ele compara e arrocha o no em imprimir o erro, so apontando pro dado dentro da lista
        if (existente -> numero_matricula==d -> numero_matricula) {
            //imprime o texto se ja existir e retorna menos zero
            puts ("Erro: Numero de matricula ja cadastrado!");
            return -1;
        }
    }
    // o código so vai chegar aqui se nao encontrar nenhuma matricula igual, chamando a função de salvar para finalizar e salvar os novo(s) discentes
   
    salvar_discente(d);
    return 0;
}

int excluir_discente_seguro(int id_discente) {
    // 1. Carregar todas as matrículas
    DAO_list matriculas = buscar_matriculas();

    // 2. Percorrer e verificar vínculo
    for (int i = 0; i < matriculas.size; i++) {
        Matricula *m = (Matricula *)matriculas.items[i];

        // 3. Encontrou vínculo - BLOQUEIA
        if (m->discente_id == id_discente) {
            puts("Nao e possivel excluir: Aluno possui matriculas vinculadas.");
            return -1;
        }
    }

    // 4. Excluir

    excluir_discente(id_discente);
    return 0;
}

DAO_list listar_discentes() {
    return buscar_discentes();
}

Discente buscar_discente_id(int id){
    return *buscar_discente(id);
}

void update_discente_id(Discente *d){
    update_discente(d);
}