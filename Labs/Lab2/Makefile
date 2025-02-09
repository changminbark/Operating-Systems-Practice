CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = heap-test

all: $(EXECS)

heap-test: heap-test.c
	$(CC) $(CFLAGS) heap-test.c -o heap-test

clean:
	/bin/rm -rf $(EXECS) *.o *~