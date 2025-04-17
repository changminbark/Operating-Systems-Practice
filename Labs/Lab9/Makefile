CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -Werror -g

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

EXECS = $(BIN)/ishell

vpath %.c $(SRC)
vpath %.h $(INC)

all: mkpaths $(EXECS)

mkpaths:
	@ mkdir -p $(OBJ) $(BIN) $(INC) $(SRC) $(DOC)

$(BIN)/ishell: $(OBJ)/ishell.o $(OBJ)/wrappers.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ)/ishell.o: ishell.c ishell.h wrappers.h
	@ mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/wrappers.o: wrappers.c wrappers.h
	@ mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

doc:
	doxygen

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* *~ $(SRC)/*~ $(INC)/*~
