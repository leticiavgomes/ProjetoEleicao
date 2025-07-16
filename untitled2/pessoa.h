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
void criar_pessoa(FILE *f, int excluidos_pessoa, struct Pessoa **pessoas);
int conferir_p(char *c, int max);
int comparar_cpf(char *c, struct Pessoa **pessoas, int total);
int comparar_titulo(char *c, struct Pessoa **pessoas, int total);
int comparar_nome(char *c, struct Pessoa **pessoas, int total);
int para_ram_p(FILE *f, struct Pessoa **pessoas);
#endif //PESSOA_H
