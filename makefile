CC = gcc
SRC_DIR = src
SRC = ${SRC_DIR}/tty-solitaire.c
CFLAGS = -W -Wall -pedantic -ansi -std=c99
OUTPUT = bin/tty-solitaire
LDFLAGS = -lncurses

tty-solitaire: ${SRC}
	${CC} ${CFLAGS} ${LDFLAGS} ${SRC} -o ${OUTPUT}

clean:
	rm -rf ${SRC_DIR}/*.o ${OUTPUT}
