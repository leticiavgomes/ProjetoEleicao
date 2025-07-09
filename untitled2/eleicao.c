#include <stdio.h>
#include "eleicao.h"
#include <string.h>



struct eleicao eleicao_ui_inserir() {
    int ano;
    printf("digite o ano: ");
    scanf("%d", &ano);
    getchar();
    char descricao[100];
    printf("digite a descricao: ");
    fgets(descricao, sizeof(descricao), stdin);
    int codigo;
    printf("digite o codigo da uf: ");
    scanf("%d", &codigo);
    return eleicao_inserir(codigo, descricao, ano);
}
struct eleicao eleicao_inserir(int codigo, char *descricao, int ano) {
    struct eleicao eleicao1;
    eleicao1.ano = ano;
    strcpy(eleicao1.descricao, descricao);
    eleicao1.codigo_eleicao = codigo;
    return eleicao1;
}


void eleicao_mostrar_por_codigo(struct eleicao eleicao, int codigo) {
    int cod;
    printf("digite o codigo para mostrar: ");
    scanf("%d", &cod);
    if (cod == codigo) {
        printf("%d\n", eleicao.codigo_eleicao);
        printf("%s\n", eleicao.descricao);
        printf("%s\n", eleicao.ano);
    }
}