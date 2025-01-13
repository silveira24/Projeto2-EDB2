#ifndef TRIE_C
#define TRIE_C

#include <stdbool.h>

#define ALFABETO 26

typedef struct Trie{
  struct Trie *filhos[ALFABETO];
  bool fim_da_palavra;
}Trie;

Trie* criar_no_trie();
void inserir_no_trie(Trie* raiz, const char* palavra);
bool buscar_trie(Trie* raiz, const char* palavra);
bool buscar_parcial_trie(Trie* raiz, const char* palavra);
void liberar_trie(Trie* raiz);
#endif