CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = cmds cmdreverse myprog

all: $(EXECS)

cmds: cmds.c
	$(CC) $(CFLAGS) cmds.c -o cmds

cmdreverse: cmdreverse.c
	$(CC) $(CFLAGS) cmdreverse.c -o cmdreverse

myprog: myprog.c
	$(CC) $(CFLAGS) myprog.c -o myprog

clean:
	/bin/rm -rf $(EXECS) *.o *~