# Makefile for calSpan and dataDump programs
# huan zhou

CC = gcc
CFLAGS = -Wall -g

# Object files
OBJS = calSpan.o dataDump.o

# Default target
all: $(OBJS)

# Rule for calSpan.o
calSpan.o: calSpan.c
	$(CC) $(CFLAGS) -c calSpan.c

# Rule for dataDump.o
dataDump.o: dataDump.c
	$(CC) $(CFLAGS) -c dataDump.c

# Test executables (for testing purposes, not required for submission)
calMain: calSpan.o calSpanMain.c
	$(CC) $(CFLAGS) calSpan.o calSpanMain.c -o calMain

dataDumpMain: dataDump.o dataDumpMain.c
	$(CC) $(CFLAGS) dataDump.o dataDumpMain.c -o dataDumpMain

# Clean target
clean:
	rm -f $(OBJS) calMain dataDumpMain