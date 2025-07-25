#include <stdio.h>
#include "gerais.h"
#include "uf.h"
#include "pessoa.h"
#include "eleicao.h"
#include "candidato_eleicao.h"
#include "voto.h"
#include "comparecimento.h"

enum {
    inserir_uf,
    mostra_ufs,
    editar_uf,
    buscar_uf,
    excluir_uf,
    inserir_pessoa,
    mostra_pessoas,
    editar_pessoa,
    buscar_pessoa,
    excluir_pessoa,
    inserir_eleicoes,
    mostra_eleicoes,
    buscar_eleicao,
    editar_eleicao,
    excluir_eleicao,
    inserir_candidato,
    mostra_candidatos,
    mostra_candidatos_ano_uf,
    mostra_candidatos_ordenados,
    excluir_candidato,
    insere_voto,
    mostra_votos_ordenados,
    mostra_voto_candidato,
    contar_votos,
    mostrar_comparecimento,
    mostrar_comparecimento_uf,
    fechar_salvar
};

int size(char path[], int sizeof_type);

int main() {
    int capacidade = 9;

    struct UF **ufs;
    FILE *f = abrir_arquivo("ufs.dat");
    int qtd = size("ufs.dat", sizeof(struct UF));
    int excluidos_uf = 0;

    struct Pessoa **pessoas;
    FILE *p = abrir_arquivo("pessoas.dat");
    int excluidos_pessoas = 0;
    int qtd_pessoas = size("pessoas.dat", sizeof(struct Pessoa));

    struct Eleicao **eleicoes;
    FILE *e = abrir_arquivo("eleicoes.dat");
    int qtd_eleicoes = size("eleicoes.dat", sizeof(struct Eleicao));
    int excluidos_eleicoes = 0;

    struct candidato_eleicao **candidatos;
    FILE *c = abrir_arquivo("candidatos.dat");
    int qtd_candidatos = size("candidatos.dat", sizeof(struct candidato_eleicao));
    int excluidos_candidatos = 0;

    struct voto **votos;
    FILE *v = abrir_arquivo("votos.dat");
    int qtd_votos = size("votos.dat", sizeof(struct voto));


    struct comparecimento **comparecimentos;
    FILE *cmp = abrir_arquivo("comparecimentos.dat");
    int qtd_cmp = size("comparecimentos.dat", sizeof(struct comparecimento));


    int opcao;

    ufs = inicia_ufs(capacidade, f, qtd);
    candidatos = inicia_candidatos(capacidade, c, qtd_candidatos);
    pessoas = inicia_pessoa(capacidade, p, qtd_pessoas);
    eleicoes = inicia_eleicoes(capacidade, e, qtd_eleicoes);
    votos = inicia_votos(capacidade, v, qtd_votos);
    comparecimentos = inicia_comparecimento(capacidade, cmp, qtd_cmp);
    para_ram(f, ufs);
    para_ram_p(p, pessoas);
    para_ram_e(e, eleicoes);
    para_ram_c(c, candidatos);
    para_ram_v(v, votos);
    para_ram_cmp(cmp, comparecimentos);
    do {
        printf("+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n\n");
        printf("OPCOES:\n\n");
        printf("0 - Inserir UF\n");
        printf("1 - Mostrar UFs\n");
        printf("2 - Editar UF\n");
        printf("3 - Buscar UF\n");
        printf("4 - Excluir UF\n");
        printf("5 - Inserir pessoa\n");
        printf("6 - Mostrar pessoas\n");
        printf("7 - Editar pessoas\n");
        printf("8 - Buscar pessoa por titulo\n");
        printf("9 - Excluir pessoa\n");
        printf("10 - Inserir eleicoes\n");
        printf("11 - Mostrar eleicoes\n");
        printf("12 - Buscar eleicao\n");
        printf("13 - Editar eleicao\n");
        printf("14 - Excluir eleicao\n");
        printf("15 - Inserir candidato\n");
        printf("16 - Mostrar candidatos\n");
        printf("17 - Buscar candidatos por ano e UF\n");
        printf("18 - Mostrar candidatos ordenados\n");
        printf("19 - Excluir candidato\n");
        printf("20 - Inserir voto\n");
        printf("21 - Mostrar votos ordenados\n");
        printf("22 - Mostrar votos por candidato\n");
        printf("23 - Contar votos\n");
        printf("24 - Mostrar comparecimento ordenado\n");
        printf("25 - Mostrar quantidade de comparecimento por uf\n");
        printf("26 - Fechar e salvar! \n\n");
        printf("+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n\n");
        printf("Digite a opcao desejada:\n");
        scanf("%d", &opcao);
        getchar();


        switch (opcao) {
            case inserir_uf:
                excluidos_uf = conta_uf_exc(ufs, qtd);
                criar_uf(excluidos_uf, ufs, qtd);
                if (excluidos_uf == 0) {
                    qtd++;
                }
                break;
            case mostra_ufs:
                mostrar_ufs(ufs, qtd);
                break;
            case editar_uf:
                editar(ufs, qtd);
                break;
            case buscar_uf:
                buscar_por_codigo(ufs, qtd);
                break;
            case excluir_uf:
                excluir(ufs, qtd);
                break;
            case inserir_pessoa:
                excluidos_pessoas = conta_pessoa_exc(pessoas, qtd_pessoas);
                criar_pessoa(qtd_pessoas, excluidos_pessoas, pessoas);
                if (excluidos_pessoas == 0) {
                    qtd_pessoas++;
                }
                break;
            case mostra_pessoas:
                mostrar_pessoas(pessoas, qtd_pessoas);
                break;
            case editar_pessoa:
                editar_p(pessoas, qtd_pessoas);
                break;
            case buscar_pessoa:
                buscar_por_titulo(pessoas, qtd_pessoas);
                break;
            case excluir_pessoa:
                excluir_p(pessoas, qtd_pessoas);
                break;
            case inserir_eleicoes:
                excluidos_eleicoes = conta_eleicoes_exc(eleicoes, qtd_eleicoes);
                criar_eleicao(excluidos_eleicoes, eleicoes, qtd_eleicoes);
                if (excluidos_eleicoes == 0) {
                    qtd_eleicoes++;
                }
                break;
            case mostra_eleicoes:
                mostrar_eleicoes(qtd_eleicoes, eleicoes);
                break;
            case buscar_eleicao:
                mostrar_eleicao(qtd_eleicoes, eleicoes);
                break;
            case editar_eleicao:
                editar_e(qtd_eleicoes, eleicoes);
                break;
            case excluir_eleicao:
                excluir_e(qtd_eleicoes, eleicoes);
                break;
            case inserir_candidato:
                excluidos_candidatos = conta_candidato_exc(candidatos, qtd_candidatos);
                criar_candidato_eleicao(qtd_candidatos, qtd_pessoas, qtd_eleicoes, excluidos_candidatos, eleicoes,
                                        pessoas, candidatos);
                if (excluidos_candidatos == 0) {
                    qtd_candidatos++;
                }
                break;
            case mostra_candidatos:
                mostrar_candidatos(qtd_candidatos, candidatos);
                break;
            case mostra_candidatos_ano_uf:
                mostrar_candidatos_ua(qtd_candidatos, qtd_eleicoes, eleicoes, candidatos);
                break;
            case mostra_candidatos_ordenados:
                mostrar_candidatos_ord(qtd_candidatos, qtd_eleicoes, eleicoes, candidatos);
                break;
            case excluir_candidato:
                excluir_c(qtd_candidatos, candidatos);
                break;
            case insere_voto:
                inserir_voto(qtd_eleicoes, qtd_pessoas, qtd_votos, qtd_candidatos, eleicoes, pessoas, comparecimentos,
                             candidatos, votos);
                qtd_votos++;
                qtd_cmp++;
                break;
            case mostra_votos_ordenados:
                mostrar_votos_ord(qtd_votos, votos);
                break;
            case mostra_voto_candidato:
                mostrar_votos_candidato(qtd_votos, votos, 1, 0, 0, 0);
                break;
            case contar_votos:
                conta_votos(qtd_votos, qtd_candidatos, votos, candidatos);
                break;
            case mostrar_comparecimento:
                mostrar_comparecimento_ord(qtd_cmp, comparecimentos);
                break;
            case mostrar_comparecimento_uf:
                mostrar_votos_comparecimento(qtd_cmp, qtd_eleicoes, comparecimentos, eleicoes, 1, 0, 0);
                break;
            case fechar_salvar:
                salvar_ufs(f, ufs, qtd);
                salvar_pessoas(p, pessoas, qtd_pessoas);
                salvar_eleicoes(e, eleicoes, qtd_eleicoes);
                salvar_candidatos(c, candidatos, qtd_candidatos);
                salvar_votos(v, votos, qtd_votos);
                salvar_comparecimentos(cmp, comparecimentos, qtd_cmp);
                break;
        }
    } while (opcao != 26);


    liberar_arquivo(ufs, f, qtd);
    liberar_arquivo_p(pessoas, p, qtd_pessoas);
    liberar_arquivo_e(eleicoes, e, qtd_eleicoes);
    liberar_arquivo_c(candidatos, c, qtd_candidatos);
    liberar_arquivo_v(votos, v, qtd_votos);
    liberar_arquivo_cmp(comparecimentos, cmp, qtd_cmp);

    return 0;
}


int size(char path[], int sizeof_type) {
    FILE *f = abrir_arquivo(path);
    fseek(f, 0,SEEK_END);
    return ftell(f) / sizeof_type;
}
