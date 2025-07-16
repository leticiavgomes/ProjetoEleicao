#include <stdio.h>
#include <string.h>
#include "pessoa.h"

#include <stdlib.h>


void criar_pessoa(FILE *f, int excluidos_pessoa, struct Pessoa **pessoas) {
    int total = 0;
    char continuar;
    do {
        pessoas[total] = malloc(sizeof(struct Pessoa));
        total = para_ram_p(f, pessoas);
        int temp = total;
        if (excluidos_pessoa>0) {
            for (int i = 0; i <total; i++) {
                if (pessoas[i]->cpf == NULL) {
                    total = i;
                    excluidos_pessoa--;
                }
            }
        }
        do {
            printf("Insira o CPF: ");
            fflush(stdin);
            gets(pessoas[total]->cpf);
            getchar();
        }while (comparar_cpf(pessoas[total]->cpf, pessoas, total)==0 || conferir_p(pessoas[total]->cpf, sizeof(pessoas[total]->cpf)==0));

        do {
            fflush(stdin);
            printf("Insira o titulo: ");
            gets(pessoas[total]->titulo);
            fflush(stdin);
        }while (comparar_titulo(pessoas[total]->titulo, pessoas, total));

        do {
            printf("Insira o nome: ");
            fflush(stdin);
            gets(pessoas[total]->nome);
        }while (comparar_nome(pessoas[total]->nome, pessoas, total)==0 || conferir_p(pessoas[total]->nome, sizeof(pessoas[total]->nome)));
        printf("digite o fone: ");
        gets(pessoas[total]->fone);
        printf("digite o endereco: ");
        gets(pessoas[total]->endereco);
        printf("digite a data de nascimento: ");
        gets(pessoas[total]->data_nasc);

        fseek(f, total*sizeof(struct Pessoa), SEEK_SET);
        fwrite(pessoas[total], sizeof(struct Pessoa), 1, f);
        total++;
        total = temp;
        printf("Continuar? (s/n): ");
        scanf(" %c", &continuar);

    }while (continuar == 's' || continuar == 'S');
}

int comparar_cpf(char *c, struct Pessoa **pessoas, int total) {
    for (int i= 0; i<total; i++) {
        if (strcmp(pessoas[i]->cpf, c)==0) {
            printf("%s ja existe! digite outro/outra. \n", c);
            return 0;
        }
        if (strlen(pessoas[i]->cpf)!=sizeof(pessoas[i]->cpf)-1) {
            printf("digite o titulo corretamente!\n");
            return 0;
        }
    }
    return 1;
}
int comparar_nome(char *c, struct Pessoa **pessoas, int total) {
    for (int i= 0; i<total; i++) {
        if (strcmp(pessoas[i]->nome, c)==0) {
            printf("%s ja existe! digite outro/outra. \n", c);
            return 0;
        }
    }
    return 1;
}
int comparar_titulo(char *c, struct Pessoa **pessoas, int total) {
    for (int i= 0; i<total; i++) {
        if (strcmp(pessoas[i]->titulo, c)==0) {
            printf("%s ja existe! digite outro/outra. \n", c);
            return 0;
        }
        if (strlen(pessoas[i]->titulo) != sizeof(pessoas[i]->titulo)){
            printf("digite o titulo corretamente! \n", c);
            return 0;
        }
    }
    return 1;
}

int conferir_p(char *c, int max) {
    if (c[0]=='\0') {
        printf("digite algo! \n");
        return 0;
    }
    if (strlen(c)>max) {
        printf("passou dos limites! ");
        return 0;
    }

    return 1;
}

int para_ram_p(FILE *f, struct Pessoa **pessoas) {

    fseek(f, 0, SEEK_END);
    int tam = ftell(f);
    fseek(f, 0, SEEK_SET);
    int qtd = tam/sizeof(struct Pessoa);
    for (int i = 0; i < qtd; i++) {
        pessoas[i] = malloc(sizeof(struct Pessoa));
        fread(pessoas[i], sizeof(struct Pessoa), 1, f);
    }
    return qtd;
}