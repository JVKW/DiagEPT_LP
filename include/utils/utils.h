#ifndef UTILS_H
#define UTILS_H
#include "cjson/cJSON.h"

int logoPrint();
void limparTela();

float lerNotaValida();

int lerInteiro();
float lerFloat();
float lerNotaValida();
char *ler_arquivo(const char *path);
void escrever_arquivo(const char *path, const char *conteudo);


void lerString(char *destino, int tamanho);

cJSON* int_array_to_json(const int *array, int size);

int* json_to_int_array(cJSON *json_array, int *size);

char * removerEspacos(char *str);

#endif