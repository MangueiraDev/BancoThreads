
EXEC = banco


CC = gcc


CFLAGS = -Wall -pthread

SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.c)


OBJS = $(SRCS:.c=.o)


all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(EXEC)
