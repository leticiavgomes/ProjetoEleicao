/* #include <stdio.h>
#include <string.h>
#include "pessoa.h"

struct Pessoa pessoa_ui_inserir() {
    char cpf[12];
    char titulo[13];
    char nome[255];
    char fone[12];
    char endereco[255];
    char data_nasc[11];
    printf("digite o CPF: ");
    fgets(cpf, sizeof(cpf), stdin);
    printf("digite o titulo: ");
    fgets(titulo, sizeof(titulo), stdin);
    printf("digite o nome: ");
    fgets(nome, sizeof(nome), stdin);
    printf("digite o fone: ");
    fgets(fone, sizeof(fone), stdin);
    printf("digite o endereco: ");
    fgets(endereco, sizeof(endereco), stdin);
    printf("digite o data_nasc: ");
    fgets(data_nasc, sizeof(data_nasc), stdin);
    return pessoa_inserir(char *cpf, char *titulo, char *nome, char *fone, char *endereco, char *data_nasc);
}

struct Pessoa pessoa_inserir(char *cpf, char *titulo, char *nome, char *fone, char *endereco, char *data_nasc) {
    struct Pessoa pessoa;
    strcpy(pessoa.cpf , cpf);
    strcpy(pessoa.titulo, titulo);
    strcpy(pessoa.nome, nome);
    strcpy(pessoa.fone, fone);
    strcpy(pessoa.endereco, endereco);
    strcpy(pessoa.data_nasc, data_nasc);
    return pessoa;

} */