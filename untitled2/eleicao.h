//
// Created by SAMSUNG on 09/07/2025.
//

#ifndef ELEICAO_H
#define ELEICAO_H

struct eleicao {
    int ano;
    char descricao[255];
    int codigo_eleicao;

};
struct eleicao eleicao_inserir(int codigo, char *descricao, int ano);
struct eleicao eleicao_ui_inserir();
void eleicao_mostrar_por_codigo(struct eleicao eleicao, int i);
#endif //ELEICAO_H
