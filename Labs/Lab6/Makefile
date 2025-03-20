CC=gcc
CFLAGS=-std=gnu99 -Wall -Werror -Wextra -g -pedantic

EXECS = dp problem1 problem2 problem3-1 problem3-2

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

problem2: problem2.o
	$(CC) $(CFLAGS) problem2.o -o problem2

problem2.o: problem2.c problem2.h
	$(CC) $(CFLAGS) -c problem2.c -o problem2.o

problem3-1: problem3-1.o
	$(CC) $(CFLAGS) problem3-1.o -o problem3-1

problem3-1.o: problem3-1.c problem3.h
	$(CC) $(CFLAGS) -c problem3-1.c -o problem3-1.o

problem3-2: problem3-2.o
	$(CC) $(CFLAGS) problem3-2.o -o problem3-2

problem3-2.o: problem3-2.c problem3.h
	$(CC) $(CFLAGS) -c problem3-2.c -o problem3-2.o

.PHONY: clean

clean: 
	/bin/rm -rf $(EXECS) *.o *~