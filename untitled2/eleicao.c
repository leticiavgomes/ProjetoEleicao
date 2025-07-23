
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pessoa.h"
#include "gerais.h"
#include "eleicao.h"

#include "uf.h"

void criar_eleicao(FILE *e, int excluidos_eleicoes, struct Eleicao **eleicoes, struct UF **ufs) {
    int total = para_ram_e(e, eleicoes);
    char continuar;
    int pos = total;
    do {
        eleicoes[pos] = malloc(sizeof(struct Eleicao));
        if (excluidos_eleicoes>0) {
            for (int i = 0; i <pos; i++) {
                if (strcmp(eleicoes[i]->descricao, "EXCLUIDO")==0) {
                    pos = i;
                    excluidos_eleicoes--;
                    break;
                }
            }
        }
        do {
            printf("Insira o ano: ");
            fflush(stdin);
            scanf("%d", &eleicoes[pos]->ano);
            printf("Insira o codigo da uf: ");
            scanf("%d", &eleicoes[pos]->codigo_uf);
        }while (confere_ano_uf(eleicoes, eleicoes[pos]->ano, eleicoes[pos]->codigo_uf, total, pos)!=1);
        printf("Digite a descricao: ");
        fflush(stdin);
        gets(eleicoes[pos]->descricao);

        fseek(e, pos*sizeof(struct Eleicao), SEEK_SET);
        fwrite(eleicoes[pos], sizeof(struct Eleicao), 1, e);
        if (pos==total) {
            pos++;
        }
        else {
            pos = total;
        }
        printf("Continuar? (s/n): ");
        scanf(" %c", &continuar);
        fflush(e);

    }while (continuar == 's' || continuar == 'S');
}


void mostrar_eleicoes(FILE *e, int capacidade) {
    struct Eleicao **eleicoes;
    eleicoes = malloc(sizeof(struct Eleicao *)*capacidade);
    int total = para_ram_e(e, eleicoes);
    printf("\n=== Eleicoes cadastradas ===\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: : %d\n", eleicoes[i]->codigo_uf);
        printf("Ano: %d\n", eleicoes[i]->ano);
        printf("Descricao: %s\n", eleicoes[i]->descricao);
    }
    for (int i = 0; i < total; ++i) {
        free(eleicoes[i]);
    }
    free(eleicoes);
}

int mostrar_eleicao(FILE *e, struct Eleicao **eleicoes) {
    int ano_e;
    int cod_uf;
    int total = para_ram_e(e, eleicoes);
    printf("Insira o ano da eleicao desejada: ");
    scanf("%d", &ano_e);
    getchar();
    printf("Digite a uf: ");
    scanf("%d", &cod_uf);
    getchar();

    for (int i = 0; i < total; i++) {
        if (eleicoes[i]->ano == ano_e && eleicoes[i]->codigo_uf == cod_uf) {
            printf("Ano: %d\n", eleicoes[i]->ano);
            printf("Codigo da UF: %d\n", eleicoes[i]->codigo_uf);
            printf("Descricao: %s\n", eleicoes[i]->descricao);
            return i;
        }
    }
    printf("Eleicao nao encontrada!\n");
    return -1;
}


void editar_e(FILE *e, struct Eleicao **eleicoes, struct UF **ufs) {
    int anoe_e;
    int cod_uf;
    int total = para_ram_e(e, eleicoes);
    printf("Digite o ano: ");
    scanf("%d", &anoe_e);
    printf("Digite o codigo da uf: ");
    scanf("%d", &cod_uf);
    for (int i = 0; i < total; ++i) {
        if (eleicoes[i]->ano == anoe_e && eleicoes[i]->codigo_uf == cod_uf) {
            printf("Achei! \n");
            do {
                printf("Insira o ano: ");
                fflush(stdin);
                scanf("%d", &eleicoes[i]->ano);
                printf("Insira o codigo da uf: ");
                scanf("%d", &eleicoes[i]->codigo_uf);
             }while (confere_ano_uf(eleicoes, eleicoes[i]->ano, eleicoes[i]->codigo_uf, total, i)==0);
            printf("Digite a descricao: ");
            fflush(stdin);
            gets(eleicoes[i]->descricao);

            fseek(e, i*sizeof(struct Eleicao), SEEK_SET);
            fwrite(eleicoes[i], sizeof(struct Eleicao), 1, e);
            fflush(e);
            break;
        }
    }
}


int confere_ano(struct Eleicao **eleicoes, int ano, int total){
    if (ano<1932) {
        printf("As primeiras eleicoes oficiais comecaram em 1932! Digite outro ano\n");
        return 0;
    }
    for (int i = 0; i < total; ++i) {
        if (eleicoes[i]->ano == ano) {
            printf("%d já está cadastrado!\n");
            return 0;
        }
    }
    return 1;
}

int confere_codigo_uf1(int inteiro, struct UF **ufs, int total) {

    for (int i= 0; i<total; i++) {
        if (ufs[i]->codigo == inteiro) {
            printf("%d está nas UFS cadastradas. \n", inteiro);
            break;
        }
        printf("UF nao encontrada ");
        return 0;
    }
}


int para_ram_e(FILE *e, struct Eleicao **eleicoes) {
    fseek(e, 0, SEEK_END);
    int tam = ftell(e);
    fseek(e, 0, SEEK_SET);
    int qtd = tam/sizeof(struct Eleicao);
    for (int i = 0; i < qtd; i++) {
        eleicoes[i] = malloc(sizeof(struct Eleicao));
        fread(eleicoes[i], sizeof(struct Eleicao), 1, e);
    }
    return qtd;
}
int confere_ano_uf(struct Eleicao **eleicoes, int ano_e, int cod_uf, int total, int ignorar_i) {
    if (ano_e<1932) {
        printf("As primeiras eleicoes oficiais comecaram em 1932! digite outro ano\n");
        return 0;
    }
    for (int i = 0; i < total; i++) {
        if (eleicoes[i]->ano == ano_e && eleicoes[i]->codigo_uf == cod_uf && i!=ignorar_i) {
            printf("eleicao de %d na UF %d existe. ", ano_e, cod_uf);
            return 2;
        }
    }
    printf("Eleicao nova/nao cadastrada! ");
    return 1;
}


void excluir_e(FILE *e, struct Eleicao **eleicoes) {
    int total = para_ram_e(e, eleicoes);
    int ano_e;
    int cod_uf;
    printf("Digite o ano: ");
    scanf("%d", &ano_e);
    printf("Digite o codigo da uf: ");
    scanf("%d", &cod_uf);
    for (int i = 0; i < total; ++i) {
        if (eleicoes[i]->ano == ano_e && eleicoes[i]->codigo_uf == cod_uf) {
            printf("Achei! \n");
            strcpy(eleicoes[i]->descricao, "EXCLUIDO");
            eleicoes[i]->ano = 0000;
            eleicoes[i]->codigo_uf = -1;
            fseek(e, i*sizeof(struct Eleicao), SEEK_SET);
            fwrite(eleicoes[i], sizeof(struct Eleicao), 1, e);
            para_ram_e(e, eleicoes);
            fflush(e);
            break;
        }
    }
    printf("Eleicao nao encontrada! ");
}

int conta_eleicoes_exc(struct Eleicao **eleicoes, int total, FILE *e) {
    para_ram_e(e, eleicoes);
    int excluido = 0;
    for (int i = 0; i < total; ++i) {
        if (strcmp(eleicoes[i]->descricao,"EXCLUIDO")==0)
            excluido++;
    }
    return excluido;
}

struct Eleicao **inicia_eleicoes(int capacidade, FILE *e, int qtd_eleicoes) {

    struct Eleicao **eleicoes;
    eleicoes = malloc(sizeof(struct Eleicao*) * capacidade);
    fseek(e, 0, SEEK_END);
    if(qtd_eleicoes+5>=capacidade){
        do{
        eleicoes = realloc(eleicoes, sizeof(struct Eleicao*)*capacidade * 2);
            capacidade = capacidade *2;
        }while (qtd_eleicoes+5>=capacidade);
    }
    for (int i = 0; i < qtd_eleicoes; i++) {
        eleicoes[i] = malloc(sizeof(struct Eleicao));
        fread(eleicoes[i], sizeof(struct Eleicao), 1, e);
    }
    return eleicoes;
}

void liberar_arquivo_e(struct Eleicao **eleicoes, FILE *e, int qtd_eleicoes) {
    for (int i = 0; i < qtd_eleicoes; i++) {
        free(eleicoes[i]);
    }
    free(eleicoes);
    fclose(e);
}
