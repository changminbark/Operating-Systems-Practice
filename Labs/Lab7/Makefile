
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = dlisttest alloc-dlist_test memory_test memory_test_1 memory_test_2 memory_test_3

all: mkpaths $(EXECS)

mkpaths:
	@ mkdir -p $(OBJ)
	@ mkdir -p $(BIN)
doc:
	doxygen

dnode.o: dnode.h dnode.c
	@ mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

dlist.o: dlist.h dlist.c dnode.h
	@ mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

allocator.o: dlist.h dlist.c dnode.h allocator.h
	@ mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

dlisttest: dlisttest.c dnode.o dlist.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest

memory_test: memory_test.c dnode.o dlist.o allocator.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory_test.c -o $(BIN)/memory_test

memory_test_1: memory_test_1.c dnode.o dlist.o allocator.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory_test_1.c -o $(BIN)/memory_test_1

memory_test_2: memory_test_2.c dnode.o dlist.o allocator.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory_test_2.c -o $(BIN)/memory_test_2

memory_test_3: memory_test_3.c dnode.o dlist.o allocator.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory_test_3.c -o $(BIN)/memory_test_3

alloc-dlist_test: alloc-dlist_test.c dnode.o dlist.o
	@ mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/alloc-dlist_test.c -o $(BIN)/alloc-dlist_test

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~ $(SRC)/*~ $(INC)/*~

