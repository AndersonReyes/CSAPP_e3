CC=gcc

LIBS=lib/Unity/src/unity.c
INCLUDES=-I.
INCLUDES += -Ichapter2/

CFLAGS=$(INCLUDES) -std=c11 -Wall -Werror -Wextra

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chapter2: chapter2/homework.o chapter2/homework_test.o $(LIBS)
	$(CC) -o $@/homework $^

test-chapter2: chapter2
	./chapter2/homework

clean:
	find . -type f -name '*.o' -delete

test: test-chapter2
