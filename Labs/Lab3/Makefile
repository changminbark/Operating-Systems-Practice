CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = char-threads

all: $(EXECS)

char-threads: char-threads.c
	$(CC) $(CFLAGS) char-threads.c -o char-threads

clean:
	/bin/rm -rf $(EXECS) *.o *~