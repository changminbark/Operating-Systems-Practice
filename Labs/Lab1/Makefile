CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = cmds cmdreverse

all: $(EXECS)

cmds: cmds.c
	$(CC) $(CFLAGS) cmds.c -o cmds

cmdreverse: cmdreverse.c
	$(CC) $(CFLAGS) cmdreverse.c -o cmdreverse

clean:
	/bin/rm -rf $(EXECS) *.o *~