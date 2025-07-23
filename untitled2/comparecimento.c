//
// Created by SAMSUNG on 22/07/2025.
//

#include "comparecimento.h"

#include <stdio.h>
#include <stdlib.h>
#include "voto.h"


void inserir_comparecimento(FILE *cmp, int ano_e, int cod_uf, struct comparecimento **comparecimentos, struct Pessoa **pessoas, FILE *p) {
    int total = para_ram_cmp(cmp, comparecimentos);
    int total_pessoas = para_ram_p(p,pessoas);
    int pos = total;
    comparecimentos[pos] = malloc(sizeof(struct comparecimento));
    comparecimentos[pos]->ano = ano_e;
    comparecimentos[pos]->codigo_uf = cod_uf;

    do{
        printf("Digite o CPF: ");
        fflush(stdin);
        gets(comparecimentos[pos]->cpf);

    }while (conferir_cpf(pessoas, total_pessoas, comparecimentos[pos]->cpf)==0);

    fseek(cmp, pos*sizeof(struct comparecimento), SEEK_SET);
    fwrite(comparecimentos[pos], sizeof(struct comparecimento), 1, cmp);
}


int mostrar_votos_comparecimento(FILE *cmp, struct comparecimento **comparecimentos, int flag, int ano_e, int uf_e) {
    int total = para_ram_cmp(cmp, comparecimentos);
    int qtd_cmp = 0;
    if (flag == 1) {
        printf("Digite o ano: ");
        scanf("%d", &ano_e);
        printf("Digite o codigo da uf: ");
        scanf("%d", &uf_e);
    }

    for (int i = 0; i < total; i++) {
            if(comparecimentos[i]->ano==ano_e && comparecimentos[i]->codigo_uf==uf_e) {
            if (flag == 1 ) {
                printf("Codigo: %d\n", comparecimentos[i]->codigo_uf);
                printf("Ano: %d\n", comparecimentos[i]->ano);
                printf("CPF: %s\n", comparecimentos[i]->cpf);
                printf("Tamanho: %d\n\n", total);
            }
            if (comparecimentos[i]->codigo_uf == uf_e && comparecimentos[i]->ano == ano_e) {
                qtd_cmp++;
            }
        }
    }
    printf("A eleicao de %d da UF %d tem %d comparecimento(s)\n",ano_e,uf_e, qtd_cmp);
    return qtd_cmp;
}

void conta_cmp(FILE *cmp, FILE *c, struct comparecimento **comparecimentos, struct candidato_eleicao **candidatos, int ano_e, int uf_e) {
    int total_cand = para_ram_c(c, candidatos);
    for (int i = 0; i < total_cand; i++) {
        if (comparecimentos[i]->ano == ano_e && comparecimentos[i]->codigo_uf == uf_e) {
            mostrar_votos_comparecimento(cmp, comparecimentos, 0, comparecimentos[i]->ano, comparecimentos[i]->codigo_uf);
        }
    }
}


int para_ram_cmp(FILE *cmp, struct comparecimento **comparecimentos) {

    fseek(cmp, 0, SEEK_END);
    int tam = ftell(cmp);
    fseek(cmp, 0, SEEK_SET);
    int qtd = tam/sizeof(struct comparecimento);
    for (int i = 0; i < qtd; i++) {
        comparecimentos[i] = malloc(sizeof(struct comparecimento));
        fread(comparecimentos[i], sizeof(struct comparecimento), 1, cmp);
    }
    return qtd;
}

void mostrar_comparecimento_ord(FILE *cmp, struct comparecimento **comparecimentos) {
    int total = para_ram_cmp(cmp, comparecimentos);
    int ano_e;
    int conta = 0;
    int k = 0;
    struct comparecimento **temp;
    struct comparecimento *aux;
    printf("digite o ano: ");
    scanf("%d", &ano_e);
    for (int i = 0; i < total; i++) {
        if(comparecimentos[i]->ano==ano_e) {
            conta++;
        }
    }
    temp = malloc(conta*sizeof(struct comparecimento*));
    for (int i = 0; i < total; i++) {
        if (comparecimentos[i]->ano==ano_e) {
            temp[k++] = comparecimentos[i];
        }
    }
    printf("Tamanho: %d\n\n", total);
    printf("\n=== Comparecimento ===\n");
    for (int i = 0; i < conta; i++) {
        for (int j = 0; j < conta-1-i; ++j) {
            if (temp[j]->codigo_uf>temp[j+1]->codigo_uf) {
                aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1]= aux;
            }
        }
    }
    for (int i = 0; i < conta; ++i) {
        printf("Codigo: %d\n", temp[i]->codigo_uf);
        printf("Ano: %d\n", temp[i]->ano);
        printf("CPF: %s\n", temp[i]->cpf);
        printf("Tamanho: %d\n\n", total);
    }
    free(temp);
}


struct comparecimento **inicia_comparecimento(int capacidade, FILE *cmp, int qtd_comparecimento) {

    struct comparecimento **comparecimentos;
    comparecimentos = malloc(sizeof(struct comparecimento*) * capacidade);
    fseek(cmp, 0, SEEK_END);
    if (qtd_comparecimento+10>=capacidade){
        do{
        comparecimentos = realloc(comparecimentos, sizeof(struct comparecimento*)*capacidade * 2);
        capacidade = capacidade *2;
        }while (qtd_comparecimento+10>=capacidade);
    }
    for (int i = 0; i < qtd_comparecimento; i++) {
        comparecimentos[i] = malloc(sizeof(struct comparecimento));
        fread(comparecimentos[i], sizeof(struct comparecimento), 1, cmp);
    }
    return comparecimentos;
}

void liberar_arquivo_cmp(struct comparecimento **comparecimentos, FILE *cmp, int qtd_cmp) {
    for (int i = 0; i < qtd_cmp; i++) {
        free(comparecimentos[i]);
    }
    free(comparecimentos);
    fclose(cmp);
}