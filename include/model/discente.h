#ifndef DISCENTE_H
#define DISCENTE_H

typedef struct Discente
{
    int id;
    char nome[256];
    int numero_matricula;
    
} Discente;

Discente* pede_captura_discente();

#endif