//
// Created by SAMSUNG on 19/07/2025.
//

#ifndef VOTO_H
#define VOTO_H
#include <stdio.h>
#include "pessoa.h"
#include "eleicao.h"
#include "candidato_eleicao.h"
#include "comparecimento.h"


struct voto{
    int ano;
    int codigo_uf;
    int numero_candidato;
    char data_hora[80];

};
int para_ram_v(FILE *v, struct voto **votos);
int conferir_voto(struct comparecimento **comparecimento, int total, int ano_e, int cod_uf, char *cpf);
void inserir_voto(int total_eleicoes, int total_pessoas, int total, int total_cand, struct  Eleicao **eleicoes, struct Pessoa **pessoas, struct comparecimento **comparecimentos, struct candidato_eleicao **candidatos, struct voto **votos);
struct voto **inicia_votos(int capacidade, FILE *v, int qtd_votos);
void mostrar_votos_ord(int total, struct voto **votos);
int mostrar_votos_candidato(int total, struct voto **votos, int flag, int ano_e, int uf_e, int numero_cand);
void conta_votos(int total_votos, int total_cand, struct voto **votos, struct candidato_eleicao **candidatos);
void liberar_arquivo_v(struct voto **votos, FILE *v, int qtd_votos);
void salvar_votos(FILE *f, struct voto **votos, int qtd_votos);

#endif //VOTO_H
