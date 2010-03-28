CC = gcc
CFLAGS = -W -Wall -pedantic -ansi -std=c99
OUTPUT = ../bin/hatneck
OBJECTS =
LDFLAGS = -lncurses

hatneck: ${OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} hatneck.c -o ${OUTPUT} ${OBJECTS}

clean:
	rm -rf *.o ${OUTPUT}
