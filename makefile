CC = clang 
CFLAGS  = -Wall -std=c99 -pedantic

main: main.o list.o memsys.o
	$(CC) $(CFLAGS) main.o list.o memsys.o -o main

main.o: list.h main.c
	$(CC) $(CFLAGS) -c main.c

list.o: memsys.h list.h list.c
	$(CC) $(CFLAGS) -c list.c

memsys.o: memsys.h
	$(CC) $(CFLAGS) -c memsys.c

clean:
	rm *.o main