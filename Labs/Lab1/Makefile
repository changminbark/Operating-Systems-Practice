CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = cmds cmdreverse myprog fork fork-test fork-wait

all: $(EXECS)

cmds: cmds.c
	$(CC) $(CFLAGS) cmds.c -o cmds

cmdreverse: cmdreverse.c
	$(CC) $(CFLAGS) cmdreverse.c -o cmdreverse

fork: fork.c
	$(CC) $(CFLAGS) fork.c -o fork

forkwait: forkwait.c
	$(CC) $(CFLAGS) fork-wait.c -o fork-wait

myprog: myprog.c
	$(CC) $(CFLAGS) myprog.c -o myprog

clean:
	/bin/rm -rf $(EXECS) *.o *~