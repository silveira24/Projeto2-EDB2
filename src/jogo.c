#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/avl.h"
#include "../include/trie.h"
#include "../include/tabuleiro.h"

void ler_tabuleiro (Tabuleiro* tabuleiro, char* caminho) {
    FILE* arquivo;
    int linhas, colunas;
    char letra;

    arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo\n");
        return;
    }

    if (fscanf(arquivo, "%d %d\n", &linhas, &colunas) != 2) {
        perror("Erro ao o tamanho do tabuleiro");
        fclose(arquivo);
        return;
    }

    tabuleiro->linhas = linhas;
    tabuleiro->colunas = colunas;

    char** novo_tabuleiro = malloc(linhas * sizeof(char*));
    if (novo_tabuleiro == NULL) {
        perror("erro ao alocar memória");
        fclose(arquivo);
        return;
    }

    for(int i = 0; i < linhas; i++) {

        novo_tabuleiro[i] = malloc(colunas * sizeof(char));
        if(novo_tabuleiro[i] == NULL) {
            perror("erro ao alocar memória");
            for(int k = 0; k < i; k++){
                free(novo_tabuleiro[k]);
            }
            free(novo_tabuleiro);
            fclose(arquivo);
            return;
        }     

        for(int j = 0; j < colunas; j++) {
            if (fscanf(arquivo, " %c", &letra) != 1) {
                perror("erro ao ler letra\n");
                for(int k = 0; k <= i; k++){
                    free(novo_tabuleiro[k]);
                }
                free(novo_tabuleiro);
                fclose(arquivo);
                return;
            }

            novo_tabuleiro[i][j] = letra;         
        }
    }

    tabuleiro->letras = novo_tabuleiro;
    fclose(arquivo);
}

void imprimir_tabuleiro(Tabuleiro tabuleiro) {
    printf("\n");
    for(int i = 0; i < tabuleiro.linhas; i++) {
        for(int j = 0; j < tabuleiro.colunas; j++) {
            printf("%c ", tabuleiro.letras[i][j]);
        }
        printf("\n");
    }
}

void liberar_tabuleiro(Tabuleiro tabuleiro) {
    for(int i = 0; i < tabuleiro.linhas; i++) {
        free(tabuleiro.letras[i]);
    }
    free(tabuleiro.letras);
}

void ler_palavras(Trie* raiz, char* caminho) {
    FILE* arquivo;
    char palavra[50];

    arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo\n");
        return;
    }

    while(fscanf(arquivo, " %49s", &palavra) == 1) {
        inserir_no_trie(raiz, palavra);
    }

    fclose(arquivo);
}

Avl* buscar_palavras(Tabuleiro tabuleiro, Trie* palavras, Avl* encontradas) {
    for (int i = 0; i < tabuleiro.linhas; i++) {
        for (int j = 0; j < tabuleiro.colunas; j++) {
            char palavra[50];
            palavra[0] = tabuleiro.letras[i][j] - 'A' + 'a';
            palavra[1] = '\0';
            if (buscar_parcial_trie(palavras, palavra)) {
                int limiteDireita = tabuleiro.colunas - j - 1;
                int limiteBaixo = tabuleiro.linhas - i - 1;
                int cont = 1;
                
                //horizontal direita
                while(cont <= limiteDireita) {
                    palavra[cont] = tabuleiro.letras[i][j + cont] - 'A' + 'a';
                    palavra[cont + 1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i, cont + j);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                
                //horizontal esquerda
                cont = 1;
                while(j - cont >= 0) {
                    palavra[cont] = tabuleiro.letras[i][j-cont] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i, j - cont);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                //vertical cima
                cont = 1;
                while(i - cont >= 0) {
                    palavra[cont] = tabuleiro.letras[i-cont][j] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i - cont, j);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                //vertical baixo
                cont = 1;
                while(cont <= limiteBaixo) {
                    palavra[cont] = tabuleiro.letras[i+cont][j] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i + cont, j);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                //diagonal direita-cima
                cont = 1;
                while(cont <= limiteDireita && i - cont >= 0) {
                    palavra[cont] = tabuleiro.letras[i-cont][j+cont] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i - cont, j + cont);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                //diagonal direita-baixo
                cont = 1;
                while(cont <= limiteDireita && cont <= limiteBaixo) {
                    palavra[cont] = tabuleiro.letras[i+cont][j+cont] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i + cont, j + cont);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                //diagonal esquerda-cima
                cont = 1;
                while(j - cont >= 0 && i - cont >= 0) {
                    palavra[cont] = tabuleiro.letras[i-cont][j-cont] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i - cont, j - cont);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
                
                //diagonal esquerda-baixo
                cont = 1;
                while(j - cont >= 0 && cont <= limiteBaixo) {
                    palavra[cont] = tabuleiro.letras[i+cont][j-cont] - 'A' + 'a';
                    palavra[cont+1] = '\0';
                    if(! buscar_parcial_trie(palavras, palavra)) {
                        palavra[1] = '\0';
                        break;
                    }
                    if(buscar_trie(palavras, palavra)) {
                        encontradas = inserir_no_avl(encontradas, palavra, i, j, i + cont, j - cont);
                        palavra[1] = '\0';
                        break;
                    }
                    cont++;
                }
            }
        }   
    }
    return encontradas;
            
}

void imprimir_resultados(Avl* encontradas) {
    imprimir_em_ordem(encontradas);
}