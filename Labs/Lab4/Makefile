CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = echod echoreq echoreq2

all: $(EXECS)

echod: echod.c wrappers.o
	$(CC) $(CFLAGS) echod.c wrappers.o -o echod

echoreq: echoreq.c wrappers.o
	$(CC) $(CFLAGS) echoreq.c wrappers.o -o echoreq

echoreq2: echoreq2.c wrappers.o
	$(CC) $(CFLAGS) echoreq2.c wrappers.o -o echoreq2

wrappers.o: wrappers.h wrappers.c
	$(CC) $(CFLAGS) -c wrappers.c -o wrappers.o

clean:
	/bin/rm -rf $(EXECS) *.o *~