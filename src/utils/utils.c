#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"
#include <string.h>
#include <ctype.h>



void limparTela() {
#ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux/macOS
#endif
}

float lerNotaValida() {
    float nota;

    do {
        printf("Digite nota (0 a 10): ");
        scanf("%f", &nota);
    } while(nota < 0 || nota > 10);

    return nota;
}

int lerInteiro() {
    char buffer[20];
    int valor;

    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return -1;
        }

        if (sscanf(buffer, "%d", &valor) == 1) {
            return valor;
        }

        printf("Valor invalido. Digite um numero inteiro: ");
    }
}

float lerFloat() {
    char buffer[20];
    float valor;

    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%f", &valor) == 1) {
            return valor;
        }

        printf("Valor inválido. Tente novamente: ");
    }
}


void lerString(char *destino, int tamanho) {
    char * sem_espacos = "";
    
    do
    {
    fgets(destino, tamanho, stdin);

    destino[strcspn(destino, "\n")] = '\0';
    
    char * sem_espacos = removerEspacosExtras(destino);
    strcpy(destino, sem_espacos);

    if (strlen(sem_espacos)>=1)
    {
        return;
    }else{
        puts("Entrada invalida! Tente novamente");
    }

    
    }while (strlen(sem_espacos)<1);

    
}

char *ler_arquivo(const char *path)
{
    FILE *f = fopen(path,"r");

    if(!f)
        return NULL;

    fseek(f,0,SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char *buffer = malloc(tamanho + 1);

    fread(buffer,1,tamanho,f);

    buffer[tamanho] = '\0';

    fclose(f);

    return buffer;
}

void escrever_arquivo(const char *path, const char *conteudo)
{
    FILE *f = fopen(path,"w");

    if(!f)
        return;

    fprintf(f,"%s",conteudo);

    fclose(f);
}

cJSON* int_array_to_json(const int *array, int size)
{
    if (array == NULL || size <= 0)
        return NULL;

    cJSON *json_array = cJSON_CreateArray();

    for (int i = 0; i < size; i++)
    {
        cJSON_AddItemToArray(json_array, cJSON_CreateNumber(array[i]));
    }

    return json_array;
}


int* json_to_int_array(cJSON *json_array, int *size)
{
    if (!cJSON_IsArray(json_array))
        return NULL;

    int count = cJSON_GetArraySize(json_array);

    int *array = malloc(sizeof(int) * count);
    if (!array)
        return NULL;

    for (int i = 0; i < count; i++)
    {
        cJSON *item = cJSON_GetArrayItem(json_array, i);

        if (cJSON_IsNumber(item))
            array[i] = item->valueint;
        else
            array[i] = 0;
    }

    *size = count;

    return array;
}

int logoPrint() {
    printf(
" _____   _                ______  _____   _______\n"
"|  __ \\ (_)              |  ____||  __ \\ |__   __|\n"
"| |  | | _   __ _   __ _ | |__   | |__) |   | |\n"
"| |  | || | / _` | / _` ||  __|  |  ___/    | |\n"
"| |__| || || (_| || (_| || |____ | |        | |\n"
"|_____/ |_| \\__,_| \\__, ||______||_|        |_|\n"
"                    __/ |\n"
"                   |___/\n"
    );

    return 0;
}

char *removerEspacos(char *str) {
    char *resultado = malloc(strlen(str) + 1);
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (!isspace((unsigned char)str[i])) {
            resultado[j++] = str[i];
        }
        i++;
    }

    resultado[j] = '\0';
    return resultado;

}

char *removerEspacosExtras(char *str) {
    char *resultado = malloc(strlen(str) + 1);
    int i = 0, j = 0;

    while (str[i] != '\0') {
        if (!isspace((unsigned char)str[i]) ||
            isspace((unsigned char)str[i]) &&
            !isspace((unsigned char)str[i+1]) &&
            i != 0 && i == strlen(str)
        ) {
            resultado[j++] = str[i];
        }
        i++;
    }

    resultado[j] = '\0';
    return resultado;

}
