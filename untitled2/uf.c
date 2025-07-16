#include "uf.h"

#define windows
//#define linux

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void excluir(FILE *f, struct UF **ufs) {
    int cod;
    int excluidos_uf = 0;
    fflush(stdin);
    scanf("%d", &cod);
    strcpy(ufs[cod]->sigla, "--");
    strcpy(ufs[cod]->descricao, "EXCLUIDO");
    fseek(f, cod*sizeof(struct UF), SEEK_SET);
    fwrite(ufs[cod], sizeof(struct UF), 1, f);
    para_ram(f,ufs);
    fflush(f);
}
void editar(FILE *f, struct UF **ufs, int total) {
    int cod;
    printf("digite o codigo para editar: ");
    fflush(stdin);
    scanf("%d", &cod);
    for (int i = 0; i < total; ++i) {
        if (ufs[i]->codigo == cod) {
            printf("achei! digite a nova sigla: \n");
            fflush(stdin);
            gets(ufs[i]->sigla);
            printf("digite a nova descricao: ");

            #ifdef windows
            fflush(stdin);
            #endif
            #ifdef linux
            fpurge(stdin);
            #endif


            gets(ufs[i]->descricao);
            fseek(f, i*sizeof(struct UF), SEEK_SET);
            fwrite(ufs[i], sizeof(struct UF), 1, f);
            fflush(f);
            break;
        }
    }
    free(ufs);
}
struct UF **buscar_por_codigo(struct UF **ufs, int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (ufs[i]->codigo == codigo) {
            printf("Codigo: %d \n", ufs[i]->codigo);
            printf("Sigla: %s \n", ufs[i]->sigla);
            printf("Descricao: %s \n", ufs[i]->descricao);
            return ufs[i];
        }

            return NULL;

    }
}


int conferir(char *c, int max) {
    if (c[0]=='\0') {
        printf("digite algo! \n");
        return 0;
    }
    if (strlen(c)>max) {
        printf("passou dos limites! ");
        return 0;
    }

    return 1;
}
int comparar_int(int a, int total, struct UF **ufs) {
    for (int i= 0; i<total; i++) {
        if (ufs[total]->codigo == ufs[i]->codigo) {
            printf("ja existe! \n");
            return 0;
        }

    }
    return 1;
}

int comparar_char(char *c, struct UF **ufs, int total) {
    for (int i= 0; i<total; i++) {
        if (strcmp(ufs[i]->sigla, c)==0) {
            printf("%s ja existe! digite outro/outra. \n", c);
            return 0;
        }
    }
    return 1;
}


FILE *abrir_arquivo(char path[]) {
    FILE *f;
    f = fopen(path, "rb+");
    if (f == NULL) {
        f = fopen(path, "wb+");

    }
    return f;
}


int para_ram(FILE *f, struct UF **ufs) {

    fseek(f, 0, SEEK_END);
    int tam = ftell(f);
    fseek(f, 0, SEEK_SET);
    int qtd = tam/sizeof(struct UF);
    for (int i = 0; i < qtd; i++) {
        ufs[i] = malloc(sizeof(struct UF));
        fread(ufs[i], sizeof(struct UF), 1, f);
    }
    return qtd;
}

void liberar_arquivo(struct UF **ufs, FILE *f) {
    int total = para_ram(f, ufs);
    for (int i = 0; i < total; i++) {
        free(ufs[i]);
    }
    free(ufs);
    fclose(f);
}

void criar_uf(FILE *f, int excluidos_uf) {

    struct UF **ufs;
    int capacidade = 30;
    char continuar;
    int total = 0;
    ufs = malloc(sizeof(struct UF *)*capacidade);

    do {
        total = para_ram(f,ufs);
        int temp = total;
        if (excluidos_uf>0) {
            for (int i = 0; i < total; i++) {
                if (strcmp(ufs[i]->descricao, "EXCLUIDO")==0) {
                    total = i;
                    excluidos_uf--;
                }
            }
        }

        int id = total;
        ufs[total] = malloc(sizeof(struct UF));
        ufs[total]->codigo = id;
        do{
            printf("Insira a sigla: ");
            gets(ufs[total]->sigla);
            for (int i = 0; i < strlen(ufs[total]->sigla); ++i) {
                ufs[total]->sigla[i] = toupper(ufs[total]->sigla[i]);
            }
        }while ((conferir(ufs[total]->sigla, 3) == 0) || (comparar_char(ufs[total]->sigla,ufs, total)==0));

        do {
            printf("Insira a descricao: ");
            gets(ufs[total]->descricao);

        }while (conferir(ufs[total]->descricao, 100) == 0);

        fseek(f, total*sizeof(struct UF), SEEK_SET);
        fwrite(ufs[total], sizeof(struct UF), 1, f);
        total++;
        total = temp;

        if (total == capacidade) {
            capacidade *= 2;
            ufs = realloc(ufs, sizeof(struct UF *)*(capacidade));
        }
        printf("continuar? ");
        scanf(" %c", &continuar);
        getchar();


    }while (continuar == 's' || continuar == 'S');
    int j;

}

void mostrar_ufs(FILE *f) {
    struct UF **ufs;
    int capacidade = 30;
    ufs = malloc(sizeof(struct UF *)*capacidade);
    int total = para_ram(f, ufs);
    printf("\n=== UF cadastradas ===\n");
    for (int i = 0; i < total; i++) {
        printf("ID: %d\n", ufs[i]->codigo);
        printf("Sigla: %s\n", ufs[i]->sigla);
        printf("Descricao: %s\n", ufs[i]->descricao);
        printf("Tamanho: %d\n\n", total);
    }

}