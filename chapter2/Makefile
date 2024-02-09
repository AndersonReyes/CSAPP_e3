CC=gcc
CFLAGS=-I. -std=c11 -Wall -Werror -Wextra

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: main.o 
	$(CC) -o prog main.o 
