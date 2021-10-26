CC = clang 
CFLAGS  = -Wall -std=c99 -pedantic

list.o: memsys.h list.h list.c
	$(CC) $(CFLAGS) -c list.c

memsys.o: memsys.h
	$(CC) $(CFLAGS) -c memsys.c

clean:
	rm *.o 
