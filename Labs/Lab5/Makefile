#
# Copyright (c) 2012 Bucknell University
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: L. Felipe Perrone (perrone@bucknell.edu)
#

CC = gcc
CFLAGS = -I./include -std=gnu99 -Wall -g #-DDEBUG
LIB = -pthread

# Object files for prodcons
PC_OBJS = $(OBJ)/prodcons.o $(OBJ)/circular_list.o

# Directories used for the software
INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS =	prodcons adt_test

all: mkpaths $(EXECS)

mkpaths:
	@ mkdir -p $(OBJ)
	@ mkdir -p $(BIN)

doc:
	doxygen

$(OBJ)/%.o: $(SRC)/%.c $(INC)/circular_list.h
	$(CC) $(CFLAGS) -c $< -o $@

prodcons: $(PC_OBJS)
	$(CC) $(PC_OBJS) -o $(BIN)/prodcons $(LIB)

# Rule for building the test object from src/adt-test.c.
$(OBJ)/adt_test.o: $(SRC)/adt_test.c $(INC)/circular_list.h
	$(CC) $(CFLAGS) -c $< -o $@

# Link the test executable.
adt_test: $(OBJ)/adt_test.o $(OBJ)/circular_list.o
	$(CC) $(OBJ)/adt_test.o $(OBJ)/circular_list.o -o $(BIN)/adt_test $(LIB)

.PHONY: clean
clean:
	/bin/rm -f $(OBJ)/* $(BIN)/* core* *~ $(SRC)/*~ $(INC)/*~ $(DOC)/*
