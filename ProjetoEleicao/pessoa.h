
//
// Created by SAMSUNG on 09/07/2025.
//

#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>

struct Pessoa{
    char cpf[12];
    char titulo[13];
    char nome[255];
    char fone[12];
    char endereco[255];
    char data_nasc[11];
};
void criar_pessoa(FILE *f, int excluidos_pessoa, struct Pessoa **pessoas);
int conferir_p(char *c, int max);
int comparar_cpf(char *c, struct Pessoa **pessoas, int total, int ignore_indice);
int comparar_titulo(char *c, struct Pessoa **pessoas, int total, int ignore_indice);
int confere_vazio(char *ch);
int para_ram_p(FILE *p, struct Pessoa **pessoas);
void mostrar_pessoas(FILE *p, int capacidade);
int buscar_por_cpf(struct Pessoa **pessoas, int total, char *achar_cpf);
int buscar_por_titulo(struct Pessoa **pessoas, int total, char *achar_titulo);
void editar_p(FILE *f, struct Pessoa **pessoas, int total);
void excluir_p(FILE *f, struct Pessoa **pessoas, int total);
int conta_pessoa_exc(struct Pessoa **pessoas, int total);
#endif //PESSOA_H
