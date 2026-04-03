#ifndef ESTADO_H
#define ESTADO_H

typedef struct Estado
{
    int totalAlunos;
    int alunosEvadidos;

    float somaTeorica;
    float somaPratica;

    float maiorNota;
    float menorNota;

    int totalAulas;
} Estado;

void inicializarEstado(Estado *e);


#endif