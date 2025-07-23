//
// Created by SAMSUNG on 18/07/2025.
//

#ifndef CANDIDATO_ELEICAO_H
#define CANDIDATO_ELEICAO_H
#include <stdio.h>
#include "uf.h"
#include "eleicao.h"
#include "pessoa.h"


struct candidato_eleicao{
    int ano;
    int codigo_uf;
    char cpf[12];
    int numero;
    int quantidade_votos;
};
void criar_candidato_eleicao(FILE *c, int excluidos_candidatos, struct  Eleicao **eleicoes, struct UF **ufs, struct Pessoa **pessoas, struct candidato_eleicao **candidatos, FILE *f, FILE *e, FILE *p);
int conferir_cpf(struct Pessoa **pessoas, int total, char *achar_cpf);
struct candidato_eleicao **inicia_candidatos(int capacidade, FILE *c, int qtd_candidatos);
int para_ram_c(FILE *c, struct candidato_eleicao **candidatos);
void mostrar_candidatos(FILE *c, struct candidato_eleicao **candidatos);
void mostrar_candidatos_ua(FILE *c, struct candidato_eleicao **candidatos);
void mostrar_candidatos_ord(FILE *c, struct candidato_eleicao **candidatos);
void excluir_c(FILE *c, struct candidato_eleicao **candidatos);
int conta_candidato_exc(struct candidato_eleicao **candidatos, int total);
int conferir_numero(FILE *c, struct candidato_eleicao **candidatos, int total, int achar_num, int ano_e, int cod_uf);
void criar_candidato2(FILE *c, int excluidos_candidatos, struct  Eleicao **eleicoes, struct UF **ufs, struct Pessoa **pessoas, struct candidato_eleicao **candidatos, FILE *f, FILE *e, FILE *p);
void liberar_arquivo_c(struct candidato_eleicao **candidatos, FILE *c, int qtd_candidatos);
int compara_cand(struct candidato_eleicao **candidatos, int qtd_candidatos, int ano_e, int cod_uf, char *cpf);
#endif //CANDIDATO_ELEICAO_H
