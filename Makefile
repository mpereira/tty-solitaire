CC      = gcc
CFLAGS  = -W -Wall -pedantic -ansi -std=c99
LDFLAGS = -lncursesw

EXECUTABLE = bin/ttysolitaire
LIB_DIR    = lib
SRC        = ${LIB_DIR}/ttysolitaire.c
LIB_OBJECTS = ${LIB_DIR}/frame.o         \
              ${LIB_DIR}/card.o          \
              ${LIB_DIR}/stack.o         \
              ${LIB_DIR}/deck.o          \
              ${LIB_DIR}/util.o          \
              ${LIB_DIR}/cursor.o        \
              ${LIB_DIR}/keyboard.o      \
              ${LIB_DIR}/display.o       \
              ${LIB_DIR}/game.o          \

TEST_EXECUTABLE = bin/ttysolitaire_test
TEST_DIR        = test
TEST_SRC        = ${TEST_DIR}/ttysolitaire_test.c
TEST_OBJECTS = ${TEST_DIR}/frame_test.o    \
               ${TEST_DIR}/card_test.o     \
               ${TEST_DIR}/stack_test.o    \
               ${TEST_DIR}/deck_test.o     \
               ${TEST_DIR}/util_test.o     \
               ${TEST_DIR}/cursor_test.o   \
               ${TEST_DIR}/keyboard_test.o \
               ${TEST_DIR}/display_test.o  \
               ${TEST_DIR}/game_test.o     \

ttysolitaire: ${LIB_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} ${SRC} -o ${EXECUTABLE} ${LIB_OBJECTS}

test: ${LIB_OBJECTS} ${TEST_OBJECTS}
	@${CC} ${CFLAGS} ${LDFLAGS} ${TEST_SRC} -o ${TEST_EXECUTABLE} ${TEST_OBJECTS} ${LIB_OBJECTS} 2> /dev/null
	@${TEST_EXECUTABLE}

clean:
	rm -rf {${LIB_DIR},${TEST_DIR}}/*.o ${EXECUTABLE} ${TEST_EXECUTABLE}
