CC = gcc
CFLAGS = -W -Wall -pedantic -ansi -std=c99
OUTPUT = ../bin/hatneck
OBJECTS =

hatneck: ${OBJECTS}
	${CC} ${CFLAGS} hatneck.c -o ${OUTPUT} ${OBJECTS}

clean:
	rm -rf *.o ${OUTPUT}
