CC=gcc
CFLAGS=-c -g -O3

main: logger.o main.o
	$(CC) logger.o main.o -o main

logger.o: logger.c
	$(CC) logger.c

main.o: main.c
	$(CC) main.c

clean:
	rm -rf *.o 
