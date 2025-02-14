# this is for a test chat-client/chat-server program
CFLAGS  = -g -Wall -Werror     ## debug option
CC      = gcc     ## compiler
SRC     = time-prime-server-thread.c time-prime-server.c time-prime-server-fork.c time-client.c tcplib.c services.c
EXE     = time-prime-server-thread time-prime-server time-prime-server-fork time-client prime-client
LIB     = tcplib-v1.o services.o
TCLNTO   = time-client.o $(LIB)
PCLNTO   = prime-client.o $(LIB)
SERVO   = time-prime-server-thread.o $(LIB)
SERVOF  = time-prime-server-fork.o $(LIB)
SERVOS  = time-prime-server.o $(LIB)
LLIB    = -lpthread #-lsocket -lnsl

all: $(EXE)

%.o: %.c services.h tcplib-v1.h
	$(CC) $(CFLAGS) -c $<

prime-client: $(PCLNTO)
	$(CC) -o $@ $(PCLNTO) $(LLIB)

time-client: $(TCLNTO)
	$(CC) -o $@ $(TCLNTO) $(LLIB)

time-prime-server-thread: $(SERVO)
	$(CC) -o $@ $(SERVO) $(LLIB)

time-prime-server: $(SERVOS)
	$(CC) -o $@ $(SERVOS) $(LLIB)

time-prime-server-fork: $(SERVOF)
	$(CC) -o $@ $(SERVOF) $(LLIB)

clean:
	/bin/rm -f core *.o $(EXE) *~
