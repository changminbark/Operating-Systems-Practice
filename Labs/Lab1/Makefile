CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = cmds

all: $(EXECS)

cmds: cmds.c
	$(CC) $(CFLAGS) cmds.c -o cmds

clean:
	/bin/rm -rf $(EXECS) *.o *~