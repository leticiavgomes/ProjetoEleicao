//
// Created by SAMSUNG on 09/07/2025.
//
#include "uf.h"

#ifndef ELEICAO_H
#define ELEICAO_H

struct Eleicao {
    int ano;
    char descricao[255];
    int codigo_uf;

};
int confere_ano(struct Eleicao **eleicoes, int ano, int total);
int confere_codigo_uf1(int inteiro, struct UF **ufs, int total);
int para_ram_e(FILE *e, struct Eleicao **eleicoes);
void criar_eleicao(FILE *e, int excluidos_eleicoes, struct Eleicao **eleicoes, struct UF **ufs);
void mostrar_eleicoes(FILE *e, int capacidade);
int mostrar_eleicao(FILE *e, struct Eleicao **eleicoes);
void editar_e(FILE *e, struct Eleicao **eleicoes, struct UF **ufs);
int confere_ano_uf(struct Eleicao **eleicoes, int ano_e, int cod_uf, int total, int ignorar_i);
void excluir_e(FILE *e, struct Eleicao **eleicoes);
int conta_eleicoes_exc(struct Eleicao **eleicoes, int total, FILE *e);
struct Eleicao **inicia_eleicoes(int capacidade, FILE *e, int qtd_eleicoes);
#endif //ELEICAO_H
