CC = gcc
CFLAGS = -std=gnu99 -Wall -Werror -g #-DDEBUG

EXECS = cmds cmdreverse myprog fork fork-wait fork-data fork-file catcount

all: $(EXECS)

catcount: catcount.c 
	$(CC) $(CFLAGS) catcount.c -o catcount

cmds: cmds.c
	$(CC) $(CFLAGS) cmds.c -o cmds

cmdreverse: cmdreverse.c
	$(CC) $(CFLAGS) cmdreverse.c -o cmdreverse

fork: fork.c
	$(CC) $(CFLAGS) fork.c -o fork

fork-wait: fork-wait.c
	$(CC) $(CFLAGS) fork-wait.c -o fork-wait

fork-data: fork-data.c
	$(CC) $(CFLAGS) fork-data.c -o fork-data

fork-file: fork-file.c 
	$(CC) $(CFLAGS) fork-file.c -o fork-file

fork-file.o: fork-file.c 
	$(CC) $(CFLAGS) -c fork-file.c 

myprog: myprog.c
	$(CC) $(CFLAGS) myprog.c -o myprog

clean:
	/bin/rm -rf $(EXECS) *.o *~