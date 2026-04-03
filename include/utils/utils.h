#ifndef UTILS_H
#define UTILS_H

void limparTela();

int lerInteiro();
float lerFloat();
float lerNotaValida();
char *ler_arquivo(const char *path);
void escrever_arquivo(const char *path, const char *conteudo);


void lerString(char *destino, int tamanho);

#endif