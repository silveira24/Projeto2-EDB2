#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/jogo.h"

int main() {
    Tabuleiro tabuleiro;
    Trie* palavras = criar_no_trie();
    Avl* encontradas = NULL;

    ler_tabuleiro(&tabuleiro, "tabuleiro.txt");
    ler_palavras(palavras, "palavras.txt");

    encontradas =  buscar_palavras(tabuleiro, palavras, encontradas);

    printf("tabuleiro lido:\n");
    imprimir_tabuleiro(tabuleiro);
    printf("\n");

    printf("palavras encontradas?\n");
    imprimir_resultados(encontradas);
    
    liberar_trie(palavras);
    liberar_tabuleiro(tabuleiro);
    liberar_avl(encontradas);

    return 0;
}