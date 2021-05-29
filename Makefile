CC = gcc
CFLAGS= -g -Wall
DEPS = RB.h

example: Example.o RB.o
	$(CC) $(CFLAGS) -o example Example.o RB.o
Example.o: Example.c $(DEPS)
	$(CC) $(CFLAGS) -c -o Example.o Example.c
RB.o: RB.c
	$(CC) $(CFLAGS) -c -o RB.o RB.c
clean:
	\rm Example.o RB.o
