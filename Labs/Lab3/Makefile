CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = char-threads mytime

all: $(EXECS)

char-threads: char-threads.c
	$(CC) $(CFLAGS) char-threads.c -o char-threads

mytime: mytime.c
	$(CC) $(CFLAGS) mytime.c -o mytime

clean:
	/bin/rm -rf $(EXECS) *.o *~