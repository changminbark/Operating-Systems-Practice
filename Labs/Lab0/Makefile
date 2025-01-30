CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = dlisttest

all: $(EXECS)

dnode.o: dnode.c dnode.h
	$(CC) $(CFLAGS) -c dnode.c -o dnode.o

dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c dlist.c -o dlist.o

dlisttest: dlisttest.c dlist.o dnode.o
	$(CC) $(CFLAGS) dlisttest.c dlist.o dnode.o -o dlisttest

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) *.o *~

