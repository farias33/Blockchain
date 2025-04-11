# Nome do executável
TARGET = blockchain

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lssl -lcrypto

# Arquivos fonte
SRCS = main.c blockchain.c block.c

# Arquivos objeto (gerados a partir dos fontes)
OBJS = $(SRCS:.c=.o)

# Regra padrão: compilar tudo
all: $(TARGET)

# Como compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Limpa arquivos objeto e executável
clean:
	rm -f $(OBJS) $(TARGET)

# Limpa apenas os objetos
clean-obj:
	rm -f $(OBJS)
