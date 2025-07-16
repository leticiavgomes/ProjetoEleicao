#include <stdio.h>
#include <stdlib.h>
#include "uf.h"

int size(char path[], int sizeof_type);

int main(void) {

    FILE *f = abrir_arquivo("ufs.dat");
    FILE *e = abrir_arquivo("ufs.dat");
    int excluidos_uf = 0;

    int size1 = size("ufs.dat", sizeof(struct UF));
    struct UF **ufs = malloc(sizeof(struct UF*) * size1);


    int qtd = size("ufs.dat", sizeof(struct UF));
    for (int i = 0; i < qtd; i++) {
        ufs[i] = malloc(sizeof(struct UF));
        fread(ufs[i], sizeof(struct UF), 1, f);
    }


    int opcao;
    do {

        printf("1 - Inserir uf\n");
        printf("2 - Imprimir uf\n");
        printf("3 - Inserir eleicao\n");
        printf("4 - buscar uf por codigo\n");
        printf("5 - Sair\n");
        printf("Digite a opcao desejada:\n");
        scanf("%d", &opcao);
        getchar();


        switch (opcao) {
            case 1:
                criar_uf(f, excluidos_uf);
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
                case 5:
                excluir(f, ufs);
                excluidos_uf++;
        }

    }while (opcao != 10);
    liberar_arquivo(ufs, f);
    fseek(e, 0, SEEK_END);

    fclose(e);

    return 0;
}


int size(char path[], int sizeof_type){
    FILE *f = abrir_arquivo(path);

    fseek(f,0,SEEK_END);

    return ftell(f) / sizeof_type;
}