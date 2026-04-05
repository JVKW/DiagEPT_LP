#include <stdio.h>
#include "controller/notas.h"
#include "utils/utils.h"
#include "model/estado.h"

void adicionarNotas(Estado *e) {
    int qtd;
    
    printf("Quantidade de alunos: ");
    scanf("%d", &qtd);
    
    e->totalAlunos += qtd;

    for (int i = 0; i < qtd; i++) {
        printf("Nota Teorica - ");
        float teorica = lerNotaValida();
        printf("Nota Pratica - ");
        float pratica = lerNotaValida();

        float media = (teorica + pratica) / 2;

        e->somaTeorica += teorica;
        e->somaPratica += pratica;
        
        if (media > e->maiorNota) e->maiorNota = media;
        if (media < e->menorNota) e->menorNota = media;
    }
}
