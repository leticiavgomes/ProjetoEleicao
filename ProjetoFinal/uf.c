#include "uf.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerais.h"


void editar(struct UF **ufs, int total) {
    int cod;

    printf("digite o codigo para editar: ");
    fflush(stdin);
    scanf("%d", &cod);
    for (int i = 0; i < total; ++i) {
        if (ufs[i]->codigo == cod) {
            do {
                fflush(stdin);
                printf("Insira a sigla: ");
                gets(ufs[i]->sigla);
                for (int j = 0; j < strlen(ufs[i]->sigla); ++j) {
                    ufs[i]->sigla[j] = toupper(ufs[i]->sigla[j]);
                }
            } while ((conferir(ufs[i]->sigla, 3) == 0) || (comparar_char(ufs[i]->sigla, ufs, total, i) == 0));

            do {
                printf("Insira a descricao: ");
                gets(ufs[i]->descricao);
            } while (conferir(ufs[i]->descricao, 100) == 0 || confere_vazio(ufs[i]->descricao) == 0);
            break;
        }
    }
}

struct UF *buscar_por_codigo(struct UF **ufs, int total) {
    printf("digite o codigo: ");
    int codigo;
    scanf("%d", &codigo);
    for (int i = 0; i < total; i++) {
        if (ufs[i]->codigo == codigo) {
            printf("Codigo: %d \n", ufs[i]->codigo);
            printf("Sigla: %s \n", ufs[i]->sigla);
            printf("Descricao: %s \n", ufs[i]->descricao);
            return ufs[i];
        }
    }
    printf("codigo nao encontrado!\n");
    return;
}


int conferir(char *c, int max) {
    if (c[0] == '\0') {
        printf("digite algo! \n");
        return 0;
    }
    if (strlen(c) > max) {
        printf("passou dos limites! ");
        return 0;
    }

    return 1;
}


int comparar_char(char *c, struct UF **ufs, int total, int ignorar_i) {
    for (int i = 0; i < total; i++) {
        if (strcmp(ufs[i]->sigla, c) == 0 && ignorar_i != i) {
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
    int qtd = tam / sizeof(struct UF);
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

int criar_uf(int excluidos_uf, struct UF **ufs, int total) {
    int pos = total;
    ufs[pos] = malloc(sizeof(struct UF));
    if (excluidos_uf > 0) {
        for (int i = 0; i < pos; i++) {
            if (strcmp(ufs[i]->descricao, "EXCLUIDO") == 0) {
                pos = i;
                break;
            }
        }
    }
    ufs[pos]->codigo = pos;
    do {
        fflush(stdin);
        printf("Insira a sigla (2 letras): ");
        scanf("%s", ufs[pos]->sigla);
        for (int j = 0; j < strlen(ufs[pos]->sigla); j++) {
            ufs[pos]->sigla[j] = toupper(ufs[pos]->sigla[j]);
        }
    } while (conferir(ufs[pos]->sigla, 3) == 0 || comparar_char(ufs[pos]->sigla, ufs, total, pos) == 0);

    do {
        fflush(stdin);
        printf("Digite a descricao: ");
        scanf(" %[^\n]", ufs[pos]->descricao);
    } while (conferir(ufs[pos]->descricao, 100) == 0 || confere_vazio(ufs[pos]->descricao) == 0);


    if (pos == total) {
        pos++;
    } else {
        pos = total;
    }


    return pos;
}


void mostrar_ufs(struct UF **ufs, int total) {
    printf("\n=== UFS cadastrados ===\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: %d\n", ufs[i]->codigo);
        printf("Sigla: %s\n", ufs[i]->sigla);
        printf("Descricao: %s\n\n", ufs[i]->descricao);
    }
}

void excluir(struct UF **ufs, int total) {
    int cod;
    printf("Digite o codigo para excluir: ");
    scanf("%d", &cod);

    for (int i = 0; i < total; i++) {
        if (ufs[i]->codigo == cod) {
            strcpy(ufs[cod]->sigla, "--");
            strcpy(ufs[cod]->descricao, "EXCLUIDO");
        }
    }
}

int conta_uf_exc(struct UF **ufs, int total) {
    int excluido = 0;
    for (int i = 0; i < total; ++i) {
        if (strcmp(ufs[i]->descricao, "EXCLUIDO") == 0)
            excluido++;
    }
    return excluido;
}


struct UF **inicia_ufs(int capacidade, FILE *f, int qtd_ufs) {
    struct UF **ufs;
    ufs = malloc(sizeof(struct UF *) * capacidade);
    if (qtd_ufs + 10 >= capacidade) {
        do {
            ufs = realloc(ufs, sizeof(struct UF *) * capacidade * 2);
            capacidade = capacidade * 2;
        } while (qtd_ufs + 5 >= capacidade);
    }
    for (int i = 0; i < qtd_ufs; i++) {
        fseek(f, i * sizeof(struct UF), SEEK_SET);
        ufs[i] = malloc(sizeof(struct UF));
        fread(ufs[i], sizeof(struct UF), 1, f);
    }
    return ufs;
}

void salvar_ufs(FILE *f, struct UF **ufs, int qtd_ufs) {
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < qtd_ufs; i++) {
        fwrite(ufs[i], sizeof(struct UF), 1, f);
    }
    fflush(f);
}
