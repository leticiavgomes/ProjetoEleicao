
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pessoa.h"
#include "gerais.h"

void criar_pessoa(int total, int excluidos_pessoa, struct Pessoa **pessoas) {
    int pos = total;

    pessoas[pos] = malloc(sizeof(struct Pessoa));
    if (excluidos_pessoa > 0) {
        for (int i = 0; i < pos; i++) {
            if (strcmp(pessoas[i]->cpf, "EXCLUIDO") == 0) {
                pos = i;
                excluidos_pessoa--;
                break;
            }
        }
    }
    do {
        printf("Insira o CPF: ");
        fflush(stdin);
        gets(pessoas[pos]->cpf);
    } while (confere_tam_char(pessoas[pos]->cpf, 11) == 0 || comparar_cpf(pessoas[pos]->cpf, pessoas, total, pos) == 0);

    do {
        fflush(stdin);
        printf("Insira o titulo: ");
        gets(pessoas[pos]->titulo);
    } while (confere_tam_char(pessoas[pos]->titulo, 12) == 0 || comparar_titulo(
                 pessoas[pos]->titulo, pessoas, total, pos) == 0);

    do {
        printf("Insira o nome: ");
        fflush(stdin);
        gets(pessoas[pos]->nome);
    } while (confere_vazio(pessoas[pos]->nome) == 0);
    printf("Digite o fone: ");
    gets(pessoas[pos]->fone);
    printf("Digite o endereco: ");
    gets(pessoas[pos]->endereco);
    printf("Digite a data de nascimento: ");
    gets(pessoas[pos]->data_nasc);
    if (pos == total) {
        pos++;
    } else {
        pos = total;
    }
}

int comparar_cpf(char *c, struct Pessoa **pessoas, int total, int ignore_indice) {
    for (int i = 0; i < total; i++) {
        if (i == ignore_indice) {
            continue;
        }
        if (strcmp(pessoas[i]->cpf, c) == 0) {
            printf("%s ja existe! digite outro.\n", c);
            return 0;
        }
    }
    return 1;
}

int comparar_titulo(char *c, struct Pessoa **pessoas, int total, int ignore_indice) {
    for (int i = 0; i < total; i++) {
        if (i == ignore_indice) {
            continue;
        }
        if (strcmp(pessoas[i]->titulo, c) == 0) {
            printf("%s existe! \n", c);
            return 0;
        }
    }
    return 1;
}


int para_ram_p(FILE *p, struct Pessoa **pessoas) {
    fseek(p, 0, SEEK_END);
    int tam = ftell(p);
    fseek(p, 0, SEEK_SET);
    int qtd = tam / sizeof(struct Pessoa);
    for (int i = 0; i < qtd; i++) {
        pessoas[i] = malloc(sizeof(struct Pessoa));
        fread(pessoas[i], sizeof(struct Pessoa), 1, p);
    }
    return qtd;
}


void mostrar_pessoas(struct Pessoa **pessoas, int total) {
    printf("\n=== Pessoas cadastradas ===\n");
    for (int i = 0; i < total; i++) {
        printf("CPF: %s\n", pessoas[i]->cpf);
        printf("Titulo: %s\n", pessoas[i]->titulo);
        printf("Nome: %s\n", pessoas[i]->nome);
        printf("Fone: %s\n", pessoas[i]->fone);
        printf("Endereco: %s\n", pessoas[i]->endereco);
        printf("Data de Nascimento: %s\n\n", pessoas[i]->data_nasc);
    }
}

int buscar_por_cpf(int total, struct Pessoa **pessoas, char *achar_cpf) {
    for (int i = 0; i < total; i++) {
        if (strcmp(pessoas[i]->cpf, achar_cpf) == 0) {
            printf("CPF: %s\n", pessoas[i]->cpf);
            printf("Titulo: %s\n", pessoas[i]->titulo);
            printf("Nome: %s\n", pessoas[i]->nome);
            printf("Fone: %s\n", pessoas[i]->fone);
            printf("Endereco: %s\n", pessoas[i]->endereco);
            printf("Data de Nascimento: %s\n\n", pessoas[i]->data_nasc);
            return i;
        }
    }
    printf("CPF nao encontrado!\n");
    return -1;
}


int buscar_por_titulo(struct Pessoa **pessoas, int total) {
    char achar_titulo[12];
    do {
        printf("Digite o titulo: ");
        fflush(stdin);
        gets(achar_titulo);
    } while (comparar_titulo(achar_titulo, pessoas, total, 0) == 0);
    for (int i = 0; i < total; i++) {
        if (strcmp(pessoas[i]->titulo, achar_titulo) == 0) {
            printf("CPF: %s\n", pessoas[i]->cpf);
            printf("Titulo: %s\n", pessoas[i]->titulo);
            printf("Nome: %s\n", pessoas[i]->nome);
            printf("Fone: %s\n", pessoas[i]->fone);
            printf("Endereco: %s\n", pessoas[i]->endereco);
            printf("Data de Nascimento: %s\n\n", pessoas[i]->data_nasc);
            return i;
        }
    }
    printf("Titulo nao encontrado!\n");
    return;
}

void editar_p(struct Pessoa **pessoas, int total) {
    char cod[12];
    printf("Digite o CPF para editar: ");
    gets(cod);
    for (int i = 0; i < total; ++i) {
        if (strcmp(pessoas[i]->cpf, cod) == 0) {
            printf("Achei! \n");
            do {
                printf("Insira o CPF: ");
                fflush(stdin);
                gets(pessoas[i]->cpf);
            } while (confere_tam_char(pessoas[i]->cpf, 11) == 0 || comparar_cpf(pessoas[i]->cpf, pessoas, total, i) ==
                     0);

            do {
                fflush(stdin);
                printf("Insira o titulo: ");
                gets(pessoas[i]->titulo);
            } while (confere_tam_char(pessoas[i]->titulo, 12) == 0 || comparar_titulo(
                         pessoas[i]->titulo, pessoas, total, i) == 0);

            do {
                printf("Insira o nome: ");
                fflush(stdin);
                gets(pessoas[i]->nome);
            } while (confere_vazio(pessoas[i]->nome) == 0);
            printf("Digite o fone: ");
            gets(pessoas[i]->fone);
            printf("Digite o endereco: ");
            gets(pessoas[i]->endereco);
            printf("Digite a data de nascimento: ");
            gets(pessoas[i]->data_nasc);
            break;
        }
    }
    printf("CPF nao encontrado! ");
}

void excluir_p(struct Pessoa **pessoas, int total) {
    char cpf_proc[12];
    int cod;
    do {
        printf("Digite o CPF para excluir: ");
        gets(cpf_proc);
        cod = buscar_por_cpf(total,pessoas, cpf_proc);
    }while (cod==-1);

    strcpy(pessoas[cod]->cpf, "EXCLUIDO");
    strcpy(pessoas[cod]->titulo, "--");
    strcpy(pessoas[cod]->nome, "--");
    strcpy(pessoas[cod]->fone, "--");
    strcpy(pessoas[cod]->endereco, "--");
    strcpy(pessoas[cod]->data_nasc, "--");
}

int conta_pessoa_exc(struct Pessoa **pessoas, int total) {
    int excluido = 0;
    for (int i = 0; i < total; ++i) {
        if (strcmp(pessoas[i]->cpf, "EXCLUIDO") == 0)
            excluido++;
    }
    return excluido;
}


struct Pessoa **inicia_pessoa(int capacidade, FILE *p, int qtd_pessoas) {
    struct Pessoa **pessoas;
    pessoas = malloc(sizeof(struct Pessoa *) * capacidade);
    fseek(p, 0, SEEK_END);
    if (qtd_pessoas + 5 >= capacidade) {
        do {
            pessoas = realloc(pessoas, sizeof(struct Pessoa *) * capacidade * 2);
            capacidade = capacidade * 2;
        } while (qtd_pessoas + 5 >= capacidade);
    }
    for (int i = 0; i < qtd_pessoas; i++) {
        pessoas[i] = malloc(sizeof(struct Pessoa));
        fread(pessoas[i], sizeof(struct Pessoa), 1, p);
    }
    return pessoas;
}

void liberar_arquivo_p(struct Pessoa **pessoas, FILE *p, int qtd_pessoas) {
    for (int i = 0; i < qtd_pessoas; i++) {
        free(pessoas[i]);
    }
    free(pessoas);
    fclose(p);
}

void salvar_pessoas(FILE *f, struct Pessoa **pessoas, int qtd_pessoas) {
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < qtd_pessoas; i++) {
        fwrite(pessoas[i], sizeof(struct Pessoa), 1, f);
    }
    fflush(f);
}
