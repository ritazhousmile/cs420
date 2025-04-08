##bitOperations.o – to build and create just an object file (.o file) after compiling your bitOperations.c module

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Target to compile just the bitOperations.o object file
bitOperations.o: bitOperations.c bitOperations.h
	$(CC) $(CFLAGS) -c bitOperations.c -o bitOperations.o

# Clean target
clean:
	rm -f *.o