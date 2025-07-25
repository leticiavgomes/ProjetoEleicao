//
// Created by SAMSUNG on 22/07/2025.
//

#ifndef COMPARECIMENTO_H
#define COMPARECIMENTO_H
#include <stdio.h>
#include "pessoa.h"
#include "candidato_eleicao.h"


struct comparecimento{
    char cpf[12];
    int ano;
    int codigo_uf;
};
int para_ram_cmp(FILE *cmp, struct comparecimento **comparecimentos);
struct comparecimento **inicia_comparecimento(int capacidade, FILE *cmp, int qtd_comparecimento);
void inserir_comparecimento(int total, int total_pessoas, int ano_e, int cod_uf, struct comparecimento **comparecimentos, struct Pessoa **pessoas);
void mostrar_comparecimento_ord(int total, struct comparecimento **comparecimentos);
void conta_cmp(int total, int total_e, struct Eleicao **eleicoes, int total_cand, struct comparecimento **comparecimentos, int ano_e, int uf_e);
int mostrar_votos_comparecimento(int total, int total_e, struct comparecimento **comparecimentos, struct Eleicao **eleicoes, int flag, int ano_e, int uf_e);
void liberar_arquivo_cmp(struct comparecimento **comparecimentos, FILE *cmp, int qtd_cmp);
void salvar_comparecimentos(FILE *f, struct comparecimento **comparecimentos, int qtd_cmp);
#endif //COMPARECIMENTO_H
