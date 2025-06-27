# Compilador e flags
CC = gcc
CFLAGS = -Wall -pthread -Iinclude

# Fontes comuns
SRC = src/main.c src/account.c src/queue.c src/utils.c src/mutex.c

# Alvo padrão
all: banco_mutex

banco_mutex: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f banco_mutex