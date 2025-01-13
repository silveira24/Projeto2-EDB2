#ifndef JOGO_H
#define JOGO_H

#include "tabuleiro.h"
#include "avl.h"
#include "trie.h"

void ler_tabuleiro (Tabuleiro* tabuleiro, char* caminho);
void imprimir_tabuleiro(Tabuleiro tabuleiro);
void liberar_tabuleiro(Tabuleiro tabuleiro);
void ler_palavras(Trie* palavras, char* caminho);
Avl* buscar_palavras(Tabuleiro tabuleiro, Trie* palavras, Avl* encontradas);
void imprimir_resultados(Avl* encontradas);

#endif