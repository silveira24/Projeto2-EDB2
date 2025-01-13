# Nome do executável
TARGET = programa

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include

# Arquivos fonte
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/avl.c $(SRC_DIR)/trie.c $(SRC_DIR)/jogo.c

# Arquivos objeto
OBJS = main.o trie.o avl.o jogo.o

# Compilador e flags
CC = gcc
CFLAGS = -I$(INCLUDE_DIR)

# Regra padrão (compilar tudo)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regra para gerar os arquivos-objeto
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)
