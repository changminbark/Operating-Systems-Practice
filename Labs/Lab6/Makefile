CC=gcc
CFLAGS=-std=gnu99 -Wall -Werror -Wextra -g -pedantic

EXECS = dp problem1

all: $(EXECS)

# This makes sure that it only recompiles dp.c if there was a change, and only compile from dp.o if there was not
dp: dp.o
	$(CC) $(CFLAGS) dp.o -o dp

dp.o: dp.c
	$(CC) $(CFLAGS) -c dp.c -o dp.o

problem1: problem1.o
	$(CC) $(CFLAGS) problem1.o -o problem1

problem1.o: problem1.c problem1.h
	$(CC) $(CFLAGS) -c problem1.c -o problem1.o

.PHONY: clean

clean: 
	/bin/rm -rf $(EXECS) *.o *~