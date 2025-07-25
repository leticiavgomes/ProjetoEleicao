#include "candidato_eleicao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"


void criar_candidato_eleicao(int total_c, int total_p, int total_e, int excluidos_candidatos, struct Eleicao **eleicoes,
                             struct Pessoa **pessoas, struct candidato_eleicao **candidatos) {
    int pos = total_c;
    candidatos[pos] = malloc(sizeof(struct candidato_eleicao));
    if (excluidos_candidatos > 0) {
        for (int i = 0; i < pos; i++) {
            if (strcmp(candidatos[i]->cpf, "EXCLUIDO") == 0) {
                pos = i;
                break;
            }
        }
    }
    do {
        do {
            printf("Insira o ano: ");
            fflush(stdin);
            scanf("%d", &candidatos[pos]->ano);
            fflush(stdin);
            printf("Insira o codigo da uf: ");
            scanf("%d", &candidatos[pos]->codigo_uf);
        } while (confere_ano_uf(eleicoes, candidatos[pos]->ano, candidatos[pos]->codigo_uf, total_e, -1) != 2);
        do {
            printf("Insira um cpf: ");
            fflush(stdin);
            gets(candidatos[pos]->cpf);
        } while (conferir_cpf(pessoas, total_p, candidatos[pos]->cpf) == 0);
    } while (compara_cand(candidatos, total_c, candidatos[pos]->ano, candidatos[pos]->codigo_uf,
                          candidatos[pos]->cpf) == 1);
    do {
        printf("Digite o numero: ");
        fflush(stdin);
        scanf("%d", &candidatos[pos]->numero);
    } while (candidatos[pos]->numero == 0);
}


void excluir_c(int total, struct candidato_eleicao **candidatos) {
    int ano_e;
    int cod_uf;
    char cpf_p[12];
    printf("digite o ano: ");
    scanf("%d", &ano_e);
    printf("digite o codigo da uf: ");
    scanf("%d", &cod_uf);
    fflush(stdin);
    printf("digite o cpf: ");
    gets(cpf_p);
    for (int i = 0; i < total; ++i) {
        if (candidatos[i]->ano == ano_e && candidatos[i]->codigo_uf == cod_uf && strcmp(candidatos[i]->cpf, cpf_p) ==
            0) {
            printf("achei! \n");
            strcpy(candidatos[i]->cpf, "EXCLUIDO");
            candidatos[i]->ano = 0;
            candidatos[i]->codigo_uf = -1;
            break;
        }
    }
}

void mostrar_candidatos(int total, struct candidato_eleicao **candidatos) {
    printf("\n=== Candidatos cadastrados ===\n");
    for (int i = 0; i < total; i++) {
        printf("Codigo: %d\n", candidatos[i]->codigo_uf);
        printf("Ano: %d\n", candidatos[i]->ano);
        printf("CPF: %s\n", candidatos[i]->cpf);
        printf("Numero: %d\n\n", candidatos[i]->numero);
    }
}

void mostrar_candidatos_ord(int total, int total_e, struct Eleicao **eleicoes, struct candidato_eleicao **candidatos) {
    int ano_e;
    do {
        printf("Digite o ano: ");
        scanf("%d", &ano_e);
    }while (confere_ano(eleicoes, ano_e, total_e )!=2);
    printf("\n=== Candidatos cadastrados ===\n");
    for (int i = 0; i < total; i++) {
        if (candidatos[i]->ano == ano_e) {
            printf("Codigo: %d\n", candidatos[i]->codigo_uf);
            printf("Ano: %d\n", candidatos[i]->ano);
            printf("CPF: %s\n", candidatos[i]->cpf);
            printf("Numero: %d\n\n", candidatos[i]->numero);
        }
    }
}

void mostrar_candidatos_ua(int total, int total_e, struct Eleicao **eleicoes, struct candidato_eleicao **candidatos) {
    int ano_e;
    int uf_e;
    do {
        printf("Digite o ano: ");
        scanf("%d", &ano_e);
        printf("Digite o codigo da uf: ");
        scanf("%d", &uf_e);
    }while (confere_ano_uf(eleicoes, ano_e, uf_e, total_e, -1 )!=2);
    printf("\n=== Candidatos cadastrados em %d na UF %d ===\n", ano_e, uf_e);
    for (int i = 0; i < total; i++)
        if (candidatos[i]->ano == ano_e && candidatos[i]->codigo_uf == uf_e) {
            printf("Codigo: %d\n", candidatos[i]->codigo_uf);
            printf("Ano: %d\n", candidatos[i]->ano);
            printf("CPF: %s\n", candidatos[i]->cpf);
            printf("Numero: %d\n\n", candidatos[i]->numero);
        }
}

int conferir_cpf(struct Pessoa **pessoas, int total, char *achar_cpf) {
    for (int i = 0; i < total; i++) {
        if (strcmp(pessoas[i]->cpf, achar_cpf) == 0) {
            return 1;
        }
    }
    printf("CPF nao encontrado!\n");
    return 0;
}


struct candidato_eleicao **inicia_candidatos(int capacidade, FILE *c, int qtd_candidatos) {
    struct candidato_eleicao **candidatos;
    candidatos = malloc(sizeof(struct candidato_eleicao *) * capacidade);
    fseek(c, 0, SEEK_END);
    if (qtd_candidatos + 10 >= capacidade) {
        do {
            candidatos = realloc(candidatos, sizeof(struct candidato_eleicao *) * capacidade * 2);
            capacidade = capacidade * 2;
        } while (qtd_candidatos + 10 >= capacidade);
    }
    for (int i = 0; i < qtd_candidatos; i++) {
        candidatos[i] = malloc(sizeof(struct candidato_eleicao));
        fread(candidatos[i], sizeof(struct candidato_eleicao), 1, c);
    }
    return candidatos;
}

int conta_candidato_exc(struct candidato_eleicao **candidatos, int total) {
    int excluido = 0;
    for (int i = 0; i < total; ++i) {
        if (strcmp(candidatos[i]->cpf, "EXCLUIDO") == 0)
            excluido++;
    }
    return excluido;
}

int para_ram_c(FILE *c, struct candidato_eleicao **candidatos) {
    fseek(c, 0, SEEK_END);
    int tam = ftell(c);
    fseek(c, 0, SEEK_SET);
    int qtd = tam / sizeof(struct candidato_eleicao);
    for (int i = 0; i < qtd; i++) {
        candidatos[i] = malloc(sizeof(struct candidato_eleicao));
        fread(candidatos[i], sizeof(struct candidato_eleicao), 1, c);
    }
    return qtd;
}

int conferir_numero(struct candidato_eleicao **candidatos, int total, int achar_num, int ano_e, int cod_uf) {
    for (int i = 0; i < total; i++) {
        if (candidatos[i]->numero == achar_num && candidatos[i]->ano == ano_e && candidatos[i]->codigo_uf == cod_uf) {
            printf("Numero esta nos registros!\n ");
            return 1;
        }
    }
    printf("Numero novo/Nao cadastrado!\n");
    return 0;
}


void liberar_arquivo_c(struct candidato_eleicao **candidatos, FILE *c, int qtd_candidatos) {
    for (int i = 0; i < qtd_candidatos; i++) {
        free(candidatos[i]);
    }
    free(candidatos);
    fclose(c);
}

int compara_cand(struct candidato_eleicao **candidatos, int qtd_candidatos, int ano_e, int cod_uf, char *cpf) {
    for (int i = 0; i < qtd_candidatos; i++) {
        if ((strcmp(candidatos[i]->cpf, cpf) == 0) && candidatos[i]->ano == ano_e && candidatos[i]->codigo_uf ==
            cod_uf) {
            printf("O candidato de CPF %d, com numero %d ja existe no ano %d! \n\n", cpf, cod_uf, ano_e);
            return 1;
        }
    }
    return 0;
}


void salvar_candidatos(FILE *f, struct candidato_eleicao **candidatos, int qtd_cand) {
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < qtd_cand; i++) {
        fwrite(candidatos[i], sizeof(struct candidato_eleicao), 1, f);
    }
    fflush(f);
}
