CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = heap-test pipe-test pipes

all: $(EXECS)

heap-test: heap-test.c
	$(CC) $(CFLAGS) heap-test.c -o heap-test

pipe-test: pipe-test.c
	$(CC) $(CFLAGS) pipe-test.c -o pipe-test

pipes: pipes.c
	$(CC) $(CFLAGS) pipes.c -o pipes

clean:
	/bin/rm -rf $(EXECS) *.o *~