CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = char-threads mytime summation summation3 summation4

all: $(EXECS)

char-threads: char-threads.c
	$(CC) $(CFLAGS) char-threads.c -o char-threads

mytime: mytime.c
	$(CC) $(CFLAGS) mytime.c -o mytime

summation: summation.c 
	$(CC) $(CFLAGS) summation.c -o summation -lm -lpthread

summation3: summation3.c 
	$(CC) $(CFLAGS) summation3.c -o summation3 -lm -lpthread

summation4: summation4.c 
	$(CC) $(CFLAGS) summation4.c -o summation4 -lm -lpthread

clean:
	/bin/rm -rf $(EXECS) *.o *~