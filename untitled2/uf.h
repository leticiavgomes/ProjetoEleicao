//
// Created by SAMSUNG on 09/07/2025.
//

#ifndef UF_H
#define UF_H

struct UF{
    int codigo;
    char descricao[255];
    char sigla[3];
};

struct UF uf_ui_inserir();
struct UF uf_ui_remover();
struct UF uf_inserir();
void uf_remover();
void uf_editar();
void uf_mostrar_todas();
void uf_mostrar_por_codigo();

#endif //UF_H
