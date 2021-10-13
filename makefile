CC = clang 
CFLAGS  = -Wall -std=c99 -pedantic

list.o: memsys.o memsys.h list.h
	$(CC) $(CFLAGS) -c array.c

memsys.o: memsys.h
	$(CC) $(CFLAGS) -c memsys.c

clean:
	rm *.o