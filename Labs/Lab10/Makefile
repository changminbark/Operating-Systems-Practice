#
# CSCI 315 Operating Systems Design
# Author: L. Felipe Perrone
# Date: 2011-04-21
# Copyright (c) 2011 Bucknell University
#
# Permission is hereby granted, free of charge, to any individual or
# institution obtaining a copy of this software and associated
# documentation files (the "Software"), to use, copy, modify, and
# distribute without restriction, provided that this copyright and
# permission notice is maintained, intact, in all copies and supporting
# documentation.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
# OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# compiler
CC = gcc

CFLAGS = -g -Wall -Werror

EXE = file_stat read_dir fdump traverse sender receiver

all: $(EXE)

file_stat: file_stat.o
	$(CC) $(CFLAGS) -o file_stat file_stat.o

file_stat.o: file_stat.c
	$(CC) $(CFLAGS) -c file_stat.c -o file_stat.o

read_dir: read_dir.o
	$(CC) -o read_dir read_dir.o

read_dir.o: read_dir.c read_dir.h
	$(CC) $(CFLAGS) -c read_dir.c -o read_dir.o

fdump: fdump.o hexdump.o
	$(CC) $(CFLAGS) -o fdump fdump.o hexdump.o

fdump.o: fdump.c hexdump.h
	$(CC) $(CFLAGS) -c fdump.c -o fdump.o

hexdump.o: hexdump.c hexdump.h
	$(CC) $(CFLAGS) -c hexdump.c -o hexdump.o

traverse: traverse.o
	$(CC) $(CFLAGS) -o traverse traverse.o

traverse.o: traverse.c read_dir.h
	$(CC) $(CFLAGS) -c traverse.c -o traverse.o

sender: sender.o
	$(CC) $(CFLAGS) -o sender sender.o

sender.o: sender.c
	$(CC) $(CFLAGS) -c sender.c -o sender.o

receiver: receiver.o
	$(CC) $(CFLAGS) -o receiver receiver.o

receiver.o: receiver.c
	$(CC) $(CFLAGS) -c receiver.c -o receiver.o

.PHONY: clean
clean:
	/bin/rm -f *~ *.o core $(EXE)
