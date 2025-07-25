

//
// Created by SAMSUNG on 09/07/2025.
//

#ifndef UF_H
#define UF_H
#include <stdio.h>

struct UF{
    int codigo;
    char sigla[3];
    char descricao[100];
};

FILE *abrir_arquivo(char caminho[]);
int para_ram(FILE *f, struct UF **ufs);
void liberar_arquivo(struct UF **ufs, FILE *f, int qtd);
int criar_uf(int excluidos_uf, struct UF **ufs,int total);
void mostrar_ufs(struct UF **ufs, int total);
int conferir(char *c, int max);
int comparar_char(char *c, struct UF **ufs, int total, int ignorar_i);
int buscar_posicao_por_codigo(FILE *f, int codigo_procurado, struct UF **ufs);
void editar(struct UF **ufs, int total);
struct UF *buscar_por_codigo(struct UF **ufs, int total);
void excluir(struct UF **ufs, int total);
int conta_uf_exc(struct UF **ufs, int total);
struct UF **inicia_ufs(int capacidade, FILE *f, int qtd_ufs);
void salvar_ufs(FILE *f, struct UF **ufs, int qtd_ufs);

#endif //UF_H
