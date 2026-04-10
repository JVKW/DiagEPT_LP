#ifndef DIAGNOSTICO_TURMA_H
#define DIAGNOSTICO_TURMA_H

typedef struct {
    float mediaGeral;
    float taxaEvasao;
    float defasagemTotal;

    int totalAlunos;

    char status[50];
} DiagnosticoTurma;

#endif