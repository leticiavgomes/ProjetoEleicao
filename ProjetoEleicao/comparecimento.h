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
void inserir_comparecimento(FILE *cmp, int ano_e, int cod_uf, struct comparecimento **comparecimentos, struct Pessoa **pessoas, FILE *p);
void mostrar_comparecimento_ord(FILE *cmp, struct comparecimento **comparecimentos);
void conta_cmp(FILE *cmp, FILE *c, struct comparecimento **comparecimentos, struct candidato_eleicao **candidatos, int ano_e, int uf_e);
int mostrar_votos_comparecimento(FILE *cmp, struct comparecimento **comparecimentos, int flag, int ano_e, int uf_e);
#endif //COMPARECIMENTO_H
