#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/jogo.h"

int main() {
    Tabuleiro tabuleiro;
    Trie* palavras = criar_no_trie();
    Avl* encontradas = NULL;
    int menu1, menu2;
    printf("1 - iniciar jogo\n0 - sair\n");
    scanf("%d", &menu1);
    while(menu1 != 0 && menu1 != 1) {
        printf("comando invalido!\n");
        printf("1 - iniciar jogo\n0 - sair\n");
        scanf("%d", &menu1);
    }
    if (menu1 == 0) {
        return 1;
    }
    
    ler_tabuleiro(&tabuleiro, "tabuleiro.txt");
    ler_palavras(palavras, "palavras.txt");
    encontradas =  buscar_palavras(tabuleiro, palavras, encontradas);

    
    do {
        printf("1 - imprimir tabuleiro\n");
        printf("2 - mostrar palavras encontradas\n");
        printf("0 - sair\n");
        scanf("%d", &menu2);
        switch (menu2) {
            case 1:
                printf("tabuleiro lido:\n");
                imprimir_tabuleiro(tabuleiro);
                printf("\n");
                break;
            case 2:
                printf("palavras encontradas:\n\n");
                imprimir_resultados(encontradas);
            case 0:
                break;
            default:
                printf("comando invalido\n");
                break;
        }

    } while (menu2 != 0);
    
    liberar_trie(palavras);
    liberar_tabuleiro(tabuleiro);
    liberar_avl(encontradas);

    return 0;
}