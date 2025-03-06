CC=gcc
CFLAGS=-std=gnu99 -Wall -Werror -Wextra -g -pedantic

EXECS = dp

all: $(EXECS)

# This makes sure that it only recompiles dp.c if there was a change, and only compile from dp.o if there was not
dp: dp.o
	$(CC) $(CFLAGS) dp.o -o dp

dp.o: dp.c
	$(CC) $(CFLAGS) -c dp.c -o dp.o

.PHONY: clean

clean: 
	/bin/rm -rf $(EXECS) *.o *~