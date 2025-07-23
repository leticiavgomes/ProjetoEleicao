
#include "uf.h"

#define windows
//#define linux

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerais.h"


void editar(FILE *f, struct UF **ufs, int total) {
    int cod;

    printf("digite o codigo para editar: ");
    fflush(stdin);
    scanf("%d", &cod);
    for (int i = 0; i < total; ++i) {
        if (ufs[i]->codigo == cod) {
            do{
                fflush(stdin);
                printf("Insira a sigla: ");
                gets(ufs[i]->sigla);
                for (int j = 0; j < strlen(ufs[i]->sigla); ++j) {
                    ufs[i]->sigla[j] = toupper(ufs[i]->sigla[j]);
                }
            }while ((conferir(ufs[i]->sigla, 3) == 0) || (comparar_char(ufs[i]->sigla,ufs, total,i)==0));

            do {
                printf("Insira a descricao: ");
                gets(ufs[i]->descricao);
            }while (conferir(ufs[i]->descricao, 100) == 0 || confere_vazio(ufs[i]->descricao)==0);

            fseek(f, i*sizeof(struct UF), SEEK_SET);
            fwrite(ufs[i], sizeof(struct UF), 1, f);
            fflush(f);
            break;
        }
    }
}
struct UF *buscar_por_codigo(struct UF **ufs, int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (ufs[i]->codigo == codigo) {
            printf("Codigo: %d \n", ufs[i]->codigo);
            printf("Sigla: %s \n", ufs[i]->sigla);
            printf("Descricao: %s \n", ufs[i]->descricao);
            return ufs[i];
        }
    }
    printf("codigo nao encontrado!\n");
    return NULL;
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


int comparar_char(char *c, struct UF **ufs, int total, int ignorar_i) {
    for (int i= 0; i<total; i++) {
        if (strcmp(ufs[i]->sigla, c)==0 && ignorar_i!=i) {
            printf("%s ja existe! digite outro. \n", c);
            return 0;
        }
    }
    return 1;
}


FILE *abrir_arquivo(char caminho[]) {
    FILE *f;
    f = fopen(caminho, "rb+");
    if (f == NULL) {
        f = fopen(caminho, "wb+");

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

void liberar_arquivo(struct UF **ufs, FILE *f, int qtd) {
    for (int i = 0; i < qtd; i++) {
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
        }while ((conferir(ufs[total]->sigla, 3) == 0) || (comparar_char(ufs[total]->sigla,ufs, total,total)==0));

        do {
            printf("Insira a descricao: ");
            fflush(stdin);
            gets(ufs[total]->descricao);

        }while (conferir(ufs[total]->descricao, 100) == 0 || confere_vazio(ufs[total]->descricao)==0);

        fseek(f, total*sizeof(struct UF), SEEK_SET);
        fwrite(ufs[total], sizeof(struct UF), 1, f);
        fflush(f);
        total++;
        total = temp;

        if (total == capacidade) {
            capacidade *= 2;
            ufs = realloc(ufs, sizeof(struct UF *)*(capacidade));
        }
        printf("Continuar?(s/n) ");
        scanf(" %c", &continuar);
        getchar();


    }while (continuar == 's' || continuar == 'S');
    int j;

}


void mostrar_ufs(FILE *f, struct UF **ufs) {
    int total = para_ram(f, ufs);
    printf("\n=== UFS cadastrados ===\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: %d\n", ufs[i]->codigo);
        printf("Sigla: %s\n", ufs[i]->sigla);
        printf("Descricao: %s\n\n", ufs[i]->descricao);
    }
}

void excluir(FILE *f, struct UF **ufs) {
    int cod;
    fflush(stdin);
    printf("Digite o codigo para excluir: ");
    scanf("%d", &cod);
    strcpy(ufs[cod]->sigla, "--");
    strcpy(ufs[cod]->descricao, "EXCLUIDO");
    fseek(f, cod*sizeof(struct UF), SEEK_SET);
    fwrite(ufs[cod], sizeof(struct UF), 1, f);
    para_ram(f,ufs);
    fflush(f);
}

int conta_uf_exc(struct UF **ufs, int total) {
    int excluido = 0;
    for (int i = 0; i < total; ++i) {
        if (strcmp(ufs[i]->descricao,"EXCLUIDO")==0)
            excluido++;
    }
    return excluido;
}


struct UF **inicia_ufs(int capacidade, FILE *f, int qtd_ufs) {

    struct UF **ufs;
    ufs = malloc(sizeof(struct UF*) * capacidade);

    if(qtd_ufs+10>=capacidade){
        ufs = realloc(ufs, sizeof(struct UF*)*capacidade * 2);
    }
    for (int i = 0; i < qtd_ufs; i++) {
        fseek(f, 0, SEEK_END);
        ufs[i] = malloc(sizeof(struct UF));
        fread(ufs[i], sizeof(struct UF), 1, f);
    }
    return ufs;
}