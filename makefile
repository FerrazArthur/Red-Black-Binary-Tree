CC = gcc
CFLAGS= -g -Wall
DEPS = RB.h

cliente: Client.o RB.o
	$(CC) $(CFLAGS) -o cliente Client.o RB.o
Client.o: Client.c $(DEPS)
	$(CC) $(CFLAGS) -c -o Client.o Client.c
RB.o: RB.c
	$(CC) $(CFLAGS) -c -o RB.o RB.c
