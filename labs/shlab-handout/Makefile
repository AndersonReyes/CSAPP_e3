# Makefile for the CS:APP Shell Lab

PROG=csh
CC=gcc
CFLAGS=-Wall -Wextra	-g

OBJECT=csh.o
SRC=csh.c

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(OBJECT)
	$(CC) $(OBJECT) -o $(PROG)

# clean up
clean:
	rm -f $(FILES) *.o *~


