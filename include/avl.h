#ifndef AVL_H
#define AVL_H

#include "coordenada.h"

typedef struct Avl{
  char* dado;
  Coordenada inicial;
  Coordenada final;
  struct Avl* esquerdo;
  struct Avl* direito;
  int altura;
}Avl;

int obter_altura(Avl* avl);
int calcular_fator_de_balanceamento(Avl* avl);
Avl* criar_no_avl(char* dado, int inicialX, int inicialY, int finalX, int finalY);
Avl* rotacao_direita(Avl* y);
Avl* rotacao_esquerda(Avl* x);
Avl* inserir_no_avl(Avl* avl, char* dado, int inicialX, int inicialY, int finalX, int finalY);
Avl* menor_valorNo(Avl* Avl);
Avl* remover_no(Avl* raiz, char* dado);
void imprimir_em_ordem(Avl* raiz);
void liberar_avl(Avl* raiz);

#endif