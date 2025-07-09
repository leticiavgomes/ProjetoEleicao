#include <stdio.h>
#include "uf.h"
#include "eleicao.h"



int main(void) {

    int opcao;
    do {
        printf("Digite a opcao desejada:\n");
        printf("1 - Inserir uf\n");
        printf("2 - Imprimir uf\n");
        printf("3 - Inserir eleicao\n");
        printf("4 - Imprimir eleicao\n");
        printf("5 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                struct UF uf1 = uf_ui_inserir();
                break;
            case 2:
                uf_mostrar_por_codigo(uf1, 1);
                break;
            case 3:
                struct eleicao eleicao2024 = eleicao_ui_inserir();
                break;
            case 4:
                eleicao_mostrar_por_codigo(eleicao2024, 1);
                break;

        }
    }while (opcao != 5);

    return 0;
}
