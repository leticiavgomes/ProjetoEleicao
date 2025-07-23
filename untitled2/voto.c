//
// Created by SAMSUNG on 19/07/2025.
//

#include "voto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "comparecimento.h"



void inserir_voto(FILE *cmp, FILE *v, FILE *c, struct  Eleicao **eleicoes, struct Pessoa **pessoas, struct comparecimento **comparecimentos, struct candidato_eleicao **candidatos, struct voto **votos, FILE *e, FILE *p) {
    int total = para_ram_v(v, votos);
    int total_cand = para_ram_c(c, candidatos);
    int total_eleicoes = para_ram_e(e,eleicoes);
    time_t agora;
    struct tm *parte_dados;

    time(&agora);
    parte_dados = localtime(&agora);
    int pos = total;
        votos[pos] = malloc(sizeof(struct voto));
        do {
            do {
                printf("Insira o ano: ");
                fflush(stdin);
                scanf("%d", &votos[pos]->ano);
                fflush(stdin);
                printf("Insira o codigo da uf: ");
                scanf("%d", &votos[pos]->codigo_uf);
            }while (confere_ano_uf(eleicoes, votos[pos]->ano, votos[pos]->codigo_uf, total_eleicoes, -1)!=2);
           do{
                printf("Digite o numero: ");
                fflush(stdin);
                scanf("%d", &votos[pos]->numero_candidato);
               fflush(stdin);
            }while (conferir_numero(c,candidatos, total_cand, votos[pos]->numero_candidato, votos[pos]->ano,votos[pos]->codigo_uf)==0);
     inserir_comparecimento(cmp, votos[pos]->ano, votos[pos]->codigo_uf, comparecimentos, pessoas, p);
     strftime(votos[pos]->data_hora, 80, "%d/%m/%Y %H:%M:%S", parte_dados);
        }while (conferir_voto(comparecimentos, total, votos[pos]->ano, votos[pos]->codigo_uf, comparecimentos[pos]->cpf)!=0);

        fseek(v, pos*sizeof(struct voto), SEEK_SET);
        fwrite(votos[pos], sizeof(struct voto), 1, v);

}

int mostrar_votos_candidato(FILE *v, struct voto **votos, int flag, int ano_e, int uf_e, int numero_cand) {
    int total = para_ram_v(v, votos);
    int qtd_votos = 0;
    if (flag == 1) {
        printf("Digite o ano: ");
        scanf("%d", &ano_e);
        printf("Digite o codigo da uf: ");
        scanf("%d", &uf_e);
        printf("Digite o numero do candidato: ");
        scanf("%d", &numero_cand);
    }

    for (int i = 0; i < total; i++) {
        if(votos[i]->ano==ano_e && votos[i]->codigo_uf==uf_e && votos[i]->numero_candidato==numero_cand) {
            if (flag == 1 ) {
                printf("Codigo: %d\n", votos[i]->codigo_uf);
                printf("Ano: %d\n", votos[i]->ano);
                printf("Numero: %d\n", votos[i]->numero_candidato);
                printf("Data: %s\n", votos[i]->data_hora);
                printf("Tamanho: %d\n\n", total);
            }
            if (votos[i]->numero_candidato == numero_cand) {
                qtd_votos++;
            }
        }
    }
    printf("o candidato %d tem %d voto(s)\n", numero_cand, qtd_votos);
    return qtd_votos;
}

void conta_votos(FILE *v, FILE *c, struct voto **votos, struct candidato_eleicao **candidatos, int ano_e) {
    int total_cand = para_ram_c(c, candidatos);
    int num_uf;
    printf("digite a UF: ");
    scanf("%d", &num_uf);
    for (int i = 0; i < total_cand; i++) {
        if (candidatos[i]->ano == ano_e && candidatos[i]->codigo_uf == num_uf) {
            candidatos[i]->quantidade_votos = mostrar_votos_candidato(v, votos, 0, candidatos[i]->ano, candidatos[i]->codigo_uf, candidatos[i]->numero);
        }
    }
}


void mostrar_votos_ord(FILE *v, struct voto **votos) {
    int total = para_ram_v(v, votos);
    int ano_e;
    int conta = 0;
    int k = 0;
    struct voto **temp;
    struct voto *aux;
    printf("Digite o ano: ");
    scanf("%d", &ano_e);
    for (int i = 0; i < total; i++) {
        if(votos[i]->ano==ano_e) {
            conta++;
        }
    }
    temp = malloc(conta*sizeof(struct voto*));
    for (int i = 0; i < total; i++) {
        if (votos[i]->ano==ano_e) {
            temp[k++] = votos[i];
        }
    }
    printf("\n=== Votos cadastrados ===\n");
    for (int i = 0; i < conta; i++) {
        for (int j = 0; j < conta-1-i; ++j) {
            if (temp[j]->codigo_uf>temp[j+1]->codigo_uf) {
                aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1]= aux;
            }
        }
    }
    for (int i = 0; i < conta; ++i) {
        printf("Codigo: %d\n", temp[i]->codigo_uf);
        printf("Ano: %d\n", temp[i]->ano);
        printf("Numero: %d\n", temp[i]->numero_candidato);
        printf("Data: %s\n", temp[i]->data_hora);
    }

    free(temp);
}


int para_ram_v(FILE *v, struct voto **votos) {
    fseek(v, 0, SEEK_END);
    int tam = ftell(v);
    fseek(v, 0, SEEK_SET);
    int qtd = tam/sizeof(struct voto);
    for (int i = 0; i < qtd; i++) {
        votos[i] = malloc(sizeof(struct voto));
        fread(votos[i], sizeof(struct voto), 1, v);
    }
    return qtd;
}
int conferir_voto(struct comparecimento **comparecimento, int total, int ano_e, int cod_uf, char *cpf) {
    for (int i = 0; i < total; i++) {
        if ((strcmp(comparecimento[i]->cpf, cpf)==0) && comparecimento[i]->ano == ano_e && comparecimento[i]->codigo_uf == cod_uf) {
            printf("Voto ja inserido!\n ");
            return 1;
        }
    }
    return 0;
}

struct voto **inicia_votos(int capacidade, FILE *v, int qtd_votos) {

    struct voto **votos;
    votos = malloc(sizeof(struct voto*) * capacidade);
    fseek(v, 0, SEEK_END);
    if (qtd_votos+10>=capacidade) {
        do{
        votos = realloc(votos, sizeof(struct voto*)*capacidade * 2);
        capacidade = capacidade *2;
        }while (qtd_votos+10>=capacidade);
    }
    for (int i = 0; i < qtd_votos; i++) {
        votos[i] = malloc(sizeof(struct voto));
        fread(votos[i], sizeof(struct voto), 1, v);
    }
    return votos;
}

void liberar_arquivo_v(struct voto **votos, FILE *v, int qtd_votos) {
    for (int i = 0; i < qtd_votos; i++) {
        free(votos[i]);
    }
    free(votos);
    fclose(v);
}

void resultados(struct candidato_eleicao **candidatos, int qtd_cmp) {
    int ano_e;
    int cod_uf;
    int conta = 0;
    int k = 0;
    struct candidato_eleicao **temp;
    struct candidato_eleicao *aux;
    printf("Digite o ano: ");
    scanf("%d", &ano_e);
    printf("Digite o codigo da UF: ");
    scanf("%d", &cod_uf);
    for (int i = 0; i < qtd_cmp; i++) {
        if(candidatos[i]->ano==ano_e && candidatos[i]->codigo_uf==cod_uf) {
            conta++;
        }
    }
    temp = malloc(conta*sizeof(struct candidatos*));
    for (int i = 0; i < qtd_cmp; i++) {
        if (candidatos[i]->ano==ano_e && candidatos[i]->codigo_uf==cod_uf) {
            temp[k++] = candidatos[i];
        }
    }
    for (int i = 0; i < conta; i++) {
        for (int j = 0; j < conta-1-i; ++j) {
            if (temp[j]->quantidade_votos<temp[j+1]->quantidade_votos) {
                aux = temp[j];
                temp[j] = temp[j+1];
                temp[j+1]= aux;
            }
        }
    }
    printf("Ganhador da Eleicao:\n ");
    printf("Codigo: %d\n", temp[0]->codigo_uf);
    printf("Ano: %d\n", temp[0]->ano);
    printf("Numero: %d\n", temp[0]->numero);
    printf("CPF: %s\n", temp[0]->cpf);
    printf("Quantidade de votos: %d\n", temp[0]->quantidade_votos);
}