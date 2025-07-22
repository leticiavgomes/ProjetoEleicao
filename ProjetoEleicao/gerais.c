
//
// Created by Alunos on 16/07/2025.
//
#include "gerais.h"

#include "uf.h"

int confere_tam_char(char *ch, int tam){
    if (ch[0]=='\0') {
        printf("digite algo! \n");
        return 0;
    }
    if(strlen(ch)>tam){
        printf("%s é muito grande!", ch);
        return 0;
    }
    if(strlen(ch)<tam){
        printf("%s é muito pequeno!", ch);
        return 0;
    }
    return 1;
}

int confere_vazio(char *ch){
    if (ch[0]=='\0') {
        printf("digite algo! \n");
        return 0;
    }
}


int size1(char path[], int sizeof_type){
    FILE *f = abrir_arquivo(path);
    fseek(f,0,SEEK_END);
    return ftell(f) / sizeof_type;
}

