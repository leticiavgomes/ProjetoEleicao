#include <stdio.h>
#include <stdlib.h>
#include "uf.h"

int size(char path[], int sizeof_type);

int main(void) {

    FILE *f = abrir_arquivo("ufs.dat");
    int capacidade = 30;

    int size1 = size("ufs.dat", sizeof(struct UF));
    struct UF **ufs = malloc(sizeof(struct UF*) * size1);


    int qtd = size("ufs.dat", sizeof(struct UF));
    ufs = malloc(sizeof(struct UF*) * capacidade);
    for (int i = 0; i < qtd; i++) {
        ufs[i] = malloc(sizeof(struct UF));
        fread(ufs[i], sizeof(struct UF), 1, f);
    }


    int opcao;
    do {
        printf("Digite a opcao desejada:\n");
        printf("1 - Inserir uf\n");
        printf("2 - Imprimir uf\n");
        printf("3 - Inserir eleicao\n");
        printf("4 - buscar uf por codigo\n");
        printf("5 - Sair\n");
        scanf("%d", &opcao);
        getchar();


        switch (opcao) {
            case 1:
                criar_uf(f);
                break;
            case 2:
                mostrar_ufs(f);
                break;
            case 3:
                editar(f, ufs, qtd);
                break;
            case 4:
                printf("digite o codigo: ");
                int codigo;
                scanf("%d", &codigo);
                buscar_por_codigo(ufs, qtd,codigo);
        }
    }while (opcao != 10);
    liberar_arquivo(ufs, f);

    return 0;
}


int size(char path[], int sizeof_type)
{
    FILE *f = abrir_arquivo(path);

    fseek(f,0,SEEK_END);

    return ftell(f) / sizeof_type;
}