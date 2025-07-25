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

int conferir_cpf(struct Pessoa **pessoas, int total, char *achar_cpf);
struct candidato_eleicao **inicia_candidatos(int capacidade, FILE *c, int qtd_candidatos);
int para_ram_c(FILE *c, struct candidato_eleicao **candidatos);
void mostrar_candidatos(int total, struct candidato_eleicao **candidatos);
void mostrar_candidatos_ua(int total, int total_e, struct Eleicao **eleicoes, struct candidato_eleicao **candidatos);
void mostrar_candidatos_ord(int total, int total_e, struct Eleicao **eleicoes, struct candidato_eleicao **candidatos);
void excluir_c(int total, struct candidato_eleicao **candidatos);
int conta_candidato_exc(struct candidato_eleicao **candidatos, int total);
int conferir_numero( struct candidato_eleicao **candidatos, int total, int achar_num, int ano_e, int cod_uf);
void criar_candidato_eleicao(int total_c, int total_p, int total_e, int excluidos_candidatos, struct  Eleicao **eleicoes, struct Pessoa **pessoas, struct candidato_eleicao **candidatos);
void liberar_arquivo_c(struct candidato_eleicao **candidatos, FILE *c, int qtd_candidatos);
int compara_cand(struct candidato_eleicao **candidatos, int qtd_candidatos, int ano_e, int cod_uf, char *cpf);
void salvar_candidatos(FILE *f, struct candidato_eleicao **candidatos, int qtd_cand);
#endif //CANDIDATO_ELEICAO_H
