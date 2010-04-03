CC = gcc
SRC_DIR = src
SRC = ${SRC_DIR}/tty-solitaire.c
CFLAGS = -W -Wall -pedantic -ansi -std=c99
OUTPUT = bin/tty-solitaire
LIB_DIR = lib
OBJECTS = ${LIB_DIR}/frame.o ${LIB_DIR}/card.o ${LIB_DIR}/display.o
LDFLAGS = -lncurses

tty-solitaire: ${OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} ${SRC} -o ${OUTPUT} ${OBJECTS}

clean:
	rm -rf ${LIB_DIR}/*.o ${OUTPUT}
