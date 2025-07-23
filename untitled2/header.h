//
// Created by SAMSUNG on 08/07/2025.
//

#ifndef HEADER_H
#define HEADER_H
struct UF{
    char codigo[3];
    char descricao[255];
    char sigla[3];
};

struct eleicao {
    int ano;
    char descricao[255];
    char codigo_uf[3];
    char codigo[10];
};

struct Pessoa{
    char cpf[12];
    char titulo[13];
    char nome[255];
    char fone[12];
    char endereco[255];
    char data_nasc[11];
};

struct candidato{
    char numero[7];
    char nome[255];
    char fone[12];
    char endereco[255];
    char data_nasc[11];
};

struct voto{
    char numero_cand[7];
    char codigo_eleicao[10];
    char data_hora[15];
};

struct comparecimento{
    char titulo_eleitor[13];
    char codigo_eleicao[10];
};




#endif //HEADER_H
