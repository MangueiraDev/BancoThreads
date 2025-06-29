
EXEC = banco


CC = gcc


CFLAGS = -Wall -pthread

SRCS = main.c banco.c
OBJS = $(SRCS:.c=.o)


all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(EXEC)
