
#include <stdio.h>
#include <stdlib.h>

#include "gerais.h"
#include "uf.h"
#include "pessoa.h"
#include "eleicao.h"
#include "candidato_eleicao.h"
#include "voto.h"
#include "comparecimento.h"

int size(char path[], int sizeof_type);

int main() {

    FILE *f = abrir_arquivo("ufs.dat");
    FILE *p = abrir_arquivo("pessoas.dat");

    int excluidos_uf = 0;
    int excluidos_pessoas = 0;
    int capacidade = 30;

    struct UF **ufs;
    ufs = malloc(sizeof(struct UF *) * capacidade);
    struct Pessoa **pessoas;
    pessoas = malloc(sizeof(struct Pessoa*) * capacidade);
    fseek(f, 0, SEEK_END);
    fseek(p, 0, SEEK_END);
    do{
        ufs = realloc(ufs, sizeof(struct Pessoa*)*capacidade * 2);
    }while(ftell(f)/sizeof(struct UF)>=capacidade);

    for (int i = 0; i < capacidade; i++) {
        pessoas[i] = malloc(sizeof(struct Pessoa));
        fread(pessoas[i], sizeof(struct Pessoa), 1, p);
    }



    int qtd = size("ufs.dat", sizeof(struct UF));
    int qtd_pessoas = size("pessoas.dat", sizeof(struct Pessoa));

    for (int i = 0; i < qtd; i++) {
        ufs[i] = malloc(sizeof(struct UF));
        fread(ufs[i], sizeof(struct UF), 1, f);
    }
struct Eleicao **eleicoes;
    FILE *e = abrir_arquivo("eleicoes.dat");
    int qtd_eleicoes = size("eleicoes.dat", sizeof(struct Eleicao));
    eleicoes = inicia_eleicoes(capacidade, e, qtd_eleicoes);
    int excluidos_eleicoes = 0;
struct candidato_eleicao **candidatos;
    FILE *c = abrir_arquivo("candidatos.dat");
    int qtd_candidatos = size("candidatos.dat", sizeof(struct candidato_eleicao));
    candidatos = inicia_candidatos(capacidade, c,qtd_candidatos);
    para_ram_c(c, candidatos);
    int excluidos_candidatos = 0;
struct voto **votos;
    FILE *v = abrir_arquivo("votos.dat");
    int qtd_votos = size("votos.dat", sizeof(struct voto));
    votos = inicia_votos(capacidade, v, qtd_votos);
    para_ram_v(v, votos);
struct comparecimento **comparecimentos;
    FILE *cmp = abrir_arquivo("comparecimentos.dat");
    comparecimentos = inicia_comparecimento(capacidade, cmp, qtd_votos);


    int opcao;

    do {
        para_ram_v(v, votos);
        para_ram_c(c, candidatos);
        para_ram_p(p, pessoas);
        para_ram(f, ufs);
        para_ram_e(e, eleicoes);
        para_ram_cmp(cmp, comparecimentos);

        printf("1 - Inserir uf\n");
        printf("2 - Imprimir uf\n");
        printf("3 - Inserir eleicao\n");
        printf("4 - Buscar uf por codigo\n");
        printf("5 - Excluir UF\n");
        printf("6 - Inserir pessoa\n");
        printf("7 - Mostrar pessoas\n");
        printf("8 - Editar pessoa por CPF\n");
        printf("9 - Achar pessoa por titulo\n");
        printf("10 - Excluir pessoa por CPF\n");
        printf("Digite a opcao desejada:\n");
        scanf("%d", &opcao);
        getchar();


        switch (opcao) {
            case 1:
                excluidos_uf = conta_uf_exc(ufs, qtd);
                printf("%d", excluidos_uf);
                criar_uf(f, excluidos_uf);
                break;
            case 2:
                mostrar_ufs(f, capacidade);
                break;
            case 3:
                editar(f, ufs, qtd);
                break;
            case 4:
                printf("digite o codigo: ");
                int codigo;
                scanf("%d", &codigo);
                buscar_por_codigo(ufs, qtd,codigo);
                break;
            case 5:
                excluir(f, ufs);
                break;
            case 6:
                excluidos_pessoas = conta_pessoa_exc(pessoas, qtd_pessoas);
                printf("%d", excluidos_pessoas);
                criar_pessoa(p, excluidos_pessoas, pessoas);
                break;
            case 7:
                mostrar_pessoas(p, capacidade);
                break;
            case 8:
                editar_p(p, pessoas,qtd_pessoas);
                break;
            case 9:
                printf("digite o titulo: ");
                char titulo[12];
                fflush(stdin);
                gets(titulo);
                buscar_por_titulo(pessoas, qtd_pessoas, titulo);
                break;
            case 10:
                excluir_p(p, pessoas, qtd_pessoas);
                break;
            case 11:
                excluidos_eleicoes = conta_eleicoes_exc(eleicoes, qtd_eleicoes, e);
                printf("%d", excluidos_eleicoes);
                criar_eleicao(e, excluidos_eleicoes, eleicoes, ufs);
                break;
            case 12:
                mostrar_eleicoes(e, capacidade);
                break;
            case 13:
                mostrar_eleicao(e, eleicoes);
                break;
            case 14:
                editar_e(e, eleicoes, ufs);
                break;
            case 15:
                excluir_e(e, eleicoes);
                break;
            case 16:
                excluidos_candidatos = conta_candidato_exc(candidatos, qtd_candidatos);
                printf("%d", excluidos_candidatos);
                criar_candidato_eleicao(c, excluidos_candidatos, eleicoes, ufs, pessoas, candidatos,f,e,p);
                break;
            case 17:
                mostrar_candidatos(c, candidatos);
                break;
            case 18:
                mostrar_candidatos_ua(c, candidatos);
                break;
            case 19:
                mostrar_candidatos_ord(c, candidatos);
                break;
            case 20:
                excluir_c(c, candidatos);
                break;
            case 21:
                inserir_voto(cmp,v,c, eleicoes, pessoas, comparecimentos, candidatos, votos, e,p);
                break;
            case 22:
                mostrar_votos_ord(v, votos);
                break;
            case 23:
                mostrar_votos_candidato(v, votos, 1, 0, 0, 0);
                break;
            case 24:
                int ano;
                printf("digite o ano da eleicao: ");
                scanf("%d", &ano);
                conta_votos(v,c, votos, candidatos, ano);
                break;
            case 25:
                mostrar_comparecimento_ord(cmp, comparecimentos);
                break;
            case 26:
                mostrar_votos_comparecimento(cmp, comparecimentos, 1, 0,0);

        }



    }while (opcao != 30);
    liberar_arquivo(ufs, f);

    fclose(f);
    fclose(p);
    return 0;
}


int size(char path[], int sizeof_type){
    FILE *f = abrir_arquivo(path);
    fseek(f,0,SEEK_END);
    return ftell(f) / sizeof_type;
}
