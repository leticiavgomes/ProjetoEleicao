//
// Created by SAMSUNG on 09/07/2025.
//

#ifndef PESSOA_H
#define PESSOA_H
struct Pessoa{
    char cpf[12];
    char titulo[13];
    char nome[255];
    char fone[12];
    char endereco[255];
    char data_nasc[11];
};
struct Pessoa pessoa_inserir(char *cpf, char *titulo, char *nome, char *fone, char *endereco, char *data_nasc);
struct Pessoa pessoa_ui_inserir();
#endif //PESSOA_H
