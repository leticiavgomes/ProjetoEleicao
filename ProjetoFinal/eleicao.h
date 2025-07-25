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
void criar_eleicao(int excluidos_eleicoes, struct Eleicao **eleicoes, int total);
void mostrar_eleicoes(int total, struct Eleicao **eleicoes);
int mostrar_eleicao(int total, struct Eleicao **eleicoes);
void editar_e(int total, struct Eleicao **eleicoes);
int confere_ano_uf(struct Eleicao **eleicoes, int ano_e, int cod_uf, int total, int ignorar_i);
void excluir_e(int total, struct Eleicao **eleicoes);
int conta_eleicoes_exc(struct Eleicao **eleicoes, int total);
struct Eleicao **inicia_eleicoes(int capacidade, FILE *e, int qtd_eleicoes);
void liberar_arquivo_e(struct Eleicao **eleicoes, FILE *e, int qtd_eleicoes);
void salvar_eleicoes(FILE *f, struct Eleicao **eleicoes, int qtd_eleicoes);
#endif //ELEICAO_H
