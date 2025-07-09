//
// Created by SAMSUNG on 09/07/2025.
//
#include <stdio.h>
#include "uf.h"
#include <string.h>


struct UF uf_ui_inserir() {
    int codigo;
    printf("digite o codigo: ");
    scanf("%d", &codigo);
    getchar();
    char descricao[100];
    printf("digite a descricao: ");
    fgets(descricao, sizeof(descricao), stdin);
    char sigla[3];
    printf("digite a sigla: ");
    fgets(sigla, sizeof(sigla), stdin);
    return uf_inserir(codigo, descricao, sigla);
}
struct UF uf_inserir(int codigo, char *descricao, char *sigla) {
    struct UF uf;
    uf.codigo = codigo;
    strcpy(uf.descricao, descricao);
    strcpy(uf.sigla, sigla);
    return uf;
}

void uf_editar() {
    printf("digite o codigo para editar: ");
    int codigo;
    scanf("%d", &codigo);


}
void uf_mostrar_por_codigo(struct UF uf, int codigo) {
    int cod;
    printf("digite o codigo para mostrar: ");
    scanf("%d", &cod);
    if (cod == codigo) {
        printf("%d\n", uf.codigo);
        printf("%s\n", uf.descricao);
        printf("%s\n", uf.sigla);
    }
}