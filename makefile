CC = gcc
CFLAGS = -Wall -Wextra -pthread -g

SRC = src
OBJ = $(SRC)/main.o $(SRC)/fila.o $(SRC)/banco.o
TARGET = banco

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC)/main.o: $(SRC)/main.c $(SRC)/fila.h $(SRC)/banco.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC)/fila.o: $(SRC)/fila.c $(SRC)/fila.h $(SRC)/banco.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC)/banco.o: $(SRC)/banco.c $(SRC)/banco.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
