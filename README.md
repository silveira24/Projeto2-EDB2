# Jogo de Caça-Palavras

## Descrição Geral

Este projeto implementa um jogo de caça-palavras em **C**, utilizando uma estrutura modular para facilitar o entendimento e manutenção. O programa realiza a busca automática de palavras no tabuleiro em todas as direções (horizontal, vertical e diagonal), validando-as por meio de uma Árvore Digital (**Trie**) e armazenando as palavras encontradas em uma Árvore AVL balanceada.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

Projeto2/  
├── include/              # Diretório para arquivos de cabeçalho  
│   ├── avl.h             # Cabeçalho da AVL  
│   ├── coordenadas.h     # Estruturas das coordenadas das palavras  
│   ├── jogo.h            # Cabeçalho da lógica do jogo  
│   ├── tabuleiro.h       # Cabeçalho para manipulação do tabuleiro  
│   └── trie.h            # Cabeçalho da Árvore Trie  
│  
├── src/                  # Diretório para arquivos-fonte  
│   ├── avl.c             # Implementação da Árvore AVL  
│   ├── jogo.c            # Lógica principal do jogo  
│   ├── main.c            # Função principal  
│   ├── tabuleiro.c       # Manipulação do tabuleiro  
│   ├── trie.c            # Implementação da Árvore Trie  
│   
├── palavras.txt          # Lista de palavras válidas para o jogo  
├── tabuleiro.txt         # Arquivo com o tabuleiro do jogo  
│  
├── .gitignore            # Arquivos e pastas ignorados pelo Git  
├── Makefile              # Automação do processo de compilação  
├── README.md             # Documentação do projeto  

## Funcionalidades

### Árvore AVL (`avl.c` e `avl.h`)

A Árvore AVL é usada para armazenar e organizar as palavras encontradas no tabuleiro em ordem alfabética.

- **Principais funções implementadas**:
  - Criação de um novo nó.
  - Inserção de palavras validadas no tabuleiro.
  - Balanceamento automático da árvore após inserções e remoções.
  - Impressão das palavras armazenadas em ordem alfabética.


### Árvore Digital (Trie) (`trie.c` e `trie.h`)

A Árvore Trie é utilizada para validar as palavras possíveis no tabuleiro.

- **Principais funções implementadas**:
  - Criação de um novo nó da Trie.
  - Inserção de palavras na Trie (carregadas do arquivo `palavras.txt`).
  - Busca de palavras para verificar sua validade.
  - Validação de sequências de caracteres formadas no tabuleiro.


### Jogo (`jogo.c`)

Este módulo contém a lógica principal do jogo.

- **Principais funções implementadas**:
  - `ler_tabuleiro`: Carrega o tabuleiro a partir do arquivo `tabuleiro.txt`.
  - `ler_palavras`: Carrega o arquivo `palavras.txt` e insere as palavras na Trie.
  - `buscar_palavras`: Busca automaticamente palavras no tabuleiro em todas as direções:
    - Horizontal (direta e inversa).
    - Vertical (direta e inversa).
    - Diagonal (direta e inversa).
  - `imprimir_resultados`: Exibe as palavras encontradas e armazenadas na AVL.


### Função Principal (`main.c`)

A função principal organiza o fluxo de execução do programa e apresenta um menu interativo para o usuário.

- **Funcionalidades do menu**:
  - Inicializar o jogo.
  - Exibir o tabuleiro.
  - Listar as palavras encontradas.
  - Sair do programa.

---

## Como Compilar e Executar

1. Certifique-se de ter o compilador **GCC** instalado.
2. Navegue até o diretório do projeto.
3. Compile o programa utilizando o `Makefile`: 
    make  
Isso irá gerar o executável programa.

4. Execute o programa:  
    ./programa


## Estrutura dos Arquivos
### palavras.txt
#### Este arquivo contém as palavras que podem ser validadas no jogo. Exemplo de conteúdo:

ganimedes
calisto
io
metis
adrasteia


### tabuleiro.txt
#### Este arquivo representa o tabuleiro do jogo em formato de matriz. Exemplo de conteúdo:

10 10  
O V W Q O L L A D G  
H A E O J K O N A Q  
I P P I T J E N U B  
M O O P A S I F A E  
A R N J V M I P D S  
L U I E E X L L I B  
I E S D P E Z E A Y  
A T E E L A R A D C  
D S F L K X E K T A  
Y C A G A P E H E T  


## Exemplo de Execução
### Entrada:
#### Arquivo palavras.txt com as seguintes palavras:

ganimedes
calisto
io
europa
himalia
elara
pasifae
sinope
leda
agape

#### Arquivo tabuleiro.txt com o tabuleiro:

10 10  
O V W Q O L L A D G  
H A E O J K O N A Q  
I P P I T J E N U B  
M O O P A S I F A E  
A R N J V M I P D S  
L U I E E X L L I B  
I E S D P E Z E A Y  
A T E E L A R A D C  
D S F L K X E K T A  
Y C A G A P E H E T  


### Saída:
#### O programa encontrará automaticamente as palavras no tabuleiro e as exibirá no terminal:

Palavras encontradas:
1. ganimedes
2. calisto
3. io
4. europa
5. himalia
6. elara
7. pasifae
8. sinope
9. leda
10. agape


## Dependências
Compilador C (GCC).  
Makefile para automatizar a compilação.  
Arquivos de texto palavras.txt e tabuleiro.txt.  


## Créditos
### Projeto desenvolvido por:

Gabriel Santos da Silveira  
Tobias dos Santos Neto