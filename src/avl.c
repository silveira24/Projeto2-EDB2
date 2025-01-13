#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/avl.h"

int obter_altura(Avl* avl) {
    if (avl == NULL)
        return -1;
    else
        return avl->altura;
}

int calcular_fator_de_balanceamento(Avl* avl) {
    if (avl == NULL)
        return 0;
    else
        return obter_altura(avl->esquerdo) - obter_altura(avl->direito);
}

Avl* criar_no_avl(char* dado, int inicialX, int inicialY, int finalX, int finalY) {
    Avl* no = (Avl*)malloc(sizeof(Avl));
    no->dado = strdup(dado);
    no->inicial.x = inicialX;
    no->inicial.y = inicialY;
    no->final.x = finalX;
    no->final.y = finalY;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 0;

    return no;
}

Avl* rotacao_direita(Avl* y) {
    if (y == NULL || y->esquerdo == NULL) {
        return y;
    }
    Avl* x = y->esquerdo;
    Avl* z = x->direito;

    x->direito = y;
    y->esquerdo = z;

    if(obter_altura(y->esquerdo) > obter_altura(y->direito))
        y->altura = 1 + obter_altura(y->esquerdo);
    else
        y->altura = 1 + obter_altura(y->direito);

    if(obter_altura(x->esquerdo) > obter_altura(x->direito))
        x->altura = 1 + obter_altura(x->esquerdo);
    else
        x->altura = 1 + obter_altura(x->direito);

    return x;
}

Avl* rotacao_esquerda(Avl* x) {
    if (x == NULL || x->direito == NULL) {
        return x;
    }
    Avl* y = x->direito;
    Avl* z = y->esquerdo;

    y->esquerdo = x;
    x->direito = z;

    if(obter_altura(x->esquerdo) > obter_altura(x->direito))
        x->altura = 1 + obter_altura(x->esquerdo);
    else
        x->altura = 1 + obter_altura(x->direito);

    if (obter_altura(y->esquerdo) > obter_altura(y->direito))
        y->altura = 1 + obter_altura(y->esquerdo);
    else
        y->altura = 1 + obter_altura(y->direito);

    return y;   
}

Avl* inserir_no_avl(Avl* avl, char* dado, int inicialX, int inicialY, int finalX, int finalY) {
    if (avl == NULL)
        return criar_no_avl(dado, inicialX, inicialY, finalX, finalY);

    if(strcmp(dado, avl->dado) < 0)
        avl->esquerdo = inserir_no_avl(avl->esquerdo, dado, inicialX, inicialY, finalX, finalY);
    else if (strcmp(dado, avl->dado) > 0)
        avl->direito = inserir_no_avl(avl->direito, dado, inicialX, inicialY, finalX, finalY);
    else
        return avl;

    if(obter_altura(avl->esquerdo) > obter_altura(avl->direito))
        avl->altura = 1 + obter_altura(avl->esquerdo);
    else
        avl->altura = 1 + obter_altura(avl->direito);

    int balanceamento = calcular_fator_de_balanceamento(avl);

    /* Caso 1: Desbalanceamento à esquerda (Rotação à direita). */
    if(balanceamento > 1 && dado < avl->esquerdo->dado)
        return rotacao_direita(avl);

    /* Caso 2: Desbalanceamento à direita (Rotação à esquerda). */
    if(balanceamento < -1 && dado > avl->direito->dado)
        return rotacao_esquerda(avl);

    /* Caso 3: Desbalanceamento esquerda-direita (Rotação dupla esquerda-direita). */
    if(balanceamento > 1 && dado > avl->esquerdo->dado){
        avl->esquerdo = rotacao_esquerda(avl->esquerdo);
        return rotacao_direita(avl);
    }

    /* Caso 4: Desbalanceamento direita-esquerda (Rotação dupla direita-esquerda). */
    if(balanceamento < -1 && dado < avl->direito->dado){
        avl->direito = rotacao_direita(avl->direito);
        return rotacao_esquerda(avl);
    }

    return avl;
}

Avl* menor_valorNo(Avl* avl) {
    Avl* atual = avl;

    while(atual->esquerdo != NULL)
        atual = atual->esquerdo;

    return atual;
}

Avl* remover_no(Avl* raiz, char* dado) {
    if(raiz == NULL)
        return raiz;

    if(strcmp(dado, raiz->dado) < 0){
        raiz->esquerdo = remover_no(raiz->esquerdo, dado);
    }else if(strcmp(dado, raiz->dado) > 0){
        raiz->direito = remover_no(raiz->direito, dado);
    }else{
        /* Nó com apenas um filho ou nenhum. */
        if((raiz->esquerdo == NULL) || (raiz->direito == NULL)){
        Avl* temp;
            
        if(raiz->esquerdo != NULL)
            temp = raiz->esquerdo;
        else
            temp = raiz->direito;
        
        /* Caso de nenhum filho. */
        if(temp == NULL){
            temp = raiz;
            raiz = NULL;
        }else{
            *raiz = *temp;
        }

        free(temp);
        }else{
        /* Caso de dois filhos: obtém o sucessor. */
        Avl* temp = menor_valorNo(raiz->direito);

        free(raiz->dado);
        raiz->dado = strdup(temp->dado);

        raiz->direito = remover_no(raiz->direito, temp->dado);
        }
    }

    /* Se a árvore tinha apenas um nó. */
    if(raiz == NULL)
        return raiz;

    if(obter_altura(raiz->esquerdo) > obter_altura(raiz->direito))
        raiz->altura = 1 + obter_altura(raiz->esquerdo);
    else
        raiz->altura = 1 + obter_altura(raiz->direito);

    int balanceamento = calcular_fator_de_balanceamento(raiz);

    /* Caso 1: Desbalanceamento à esquerda. */
    if(balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) >= 0)
        return rotacao_direita(raiz);

    /* Caso 2: Desbalanceamento esquerda-direita. */
    if(balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) < 0){
        raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
        return rotacao_direita(raiz);
    }

    /* Caso 3: Desbalanceamento à direita. */
    if(balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) <= 0)
        return rotacao_esquerda(raiz);

    /* Caso 4: Desbalanceamento direita-esquerda. */
    if(balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) > 0){
        raiz->direito = rotacao_direita(raiz->direito);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

void imprimir_em_ordem(Avl* raiz) {
    if(raiz != NULL){
        imprimir_em_ordem(raiz->esquerdo);
        printf("coordenada inicial: %d %d\n", raiz->inicial.x + 1, raiz->inicial.y + 1);
        printf("coordenada final: %d %d\n", raiz->final.x + 1, raiz->final.y + 1);
        printf("palavra: %s \n\n", raiz->dado);
        imprimir_em_ordem(raiz->direito);
    }
}

void liberar_avl(Avl* raiz) {
    if (raiz == NULL) {
        return;
    }

    liberar_avl(raiz->esquerdo);
    liberar_avl(raiz->direito);

    free(raiz->dado);
    free(raiz);
}