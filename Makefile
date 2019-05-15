VERSION = 1.1.1

CC     ?= gcc
CFLAGS ?= -g
CFLAGS += -W -Wall -pedantic -ansi -std=c99 -DVERSION=\"$(VERSION)\"

# OS X installs ncurses with wide character support, but not as "libncurses".
ifeq ($(shell uname -s),Darwin)
	LDFLAGS += -lncurses
else
	LDFLAGS += -lncursesw
endif

PREFIX ?= /usr/local

EXECUTABLE = ttysolitaire
SRC_DIR    = src
SRC        = $(SRC_DIR)/ttysolitaire.c
SRC_OBJECTS = $(SRC_DIR)/common.o   \
              $(SRC_DIR)/frame.o    \
              $(SRC_DIR)/card.o     \
              $(SRC_DIR)/stack.o    \
              $(SRC_DIR)/deck.o     \
              $(SRC_DIR)/cursor.o   \
              $(SRC_DIR)/keyboard.o \
              $(SRC_DIR)/gui.o      \
              $(SRC_DIR)/game.o     \

TESTS_EXECUTABLE = ttysolitaire_test
TESTS_DIR        = tests
TESTS_SRC        = $(TESTS_DIR)/ttysolitaire_test.c
TESTS_OBJECTS = $(TESTS_DIR)/frame_test.o       \
                $(TESTS_DIR)/card_test.o        \
                $(TESTS_DIR)/stack_test.o       \
                $(TESTS_DIR)/deck_test.o        \
                $(TESTS_DIR)/cursor_test.o      \
                $(TESTS_DIR)/keyboard_test.o    \
                $(TESTS_DIR)/gui_test.o         \
                $(TESTS_DIR)/game_test.o        \
                $(TESTS_DIR)/test_helper.o      \
                $(TESTS_DIR)/test_helper_test.o \

.PHONY: test clean install uninstall

all: ${EXECUTABLE}

ttysolitaire: $(SRC_OBJECTS)
	$(CC) $(CFLAGS) $(SRC) -o $(EXECUTABLE) $(SRC_OBJECTS) $(LDFLAGS)

test: $(SRC_OBJECTS) $(TESTS_OBJECTS)
	@$(CC) $(CFLAGS) $(TESTS_SRC) -o $(TESTS_EXECUTABLE) $(TESTS_OBJECTS) $(SRC_OBJECTS) $(LDFLAGS)
	@./$(TESTS_EXECUTABLE)

clean:
	@rm -rf $(SRC_DIR)/*.o $(TESTS_DIR)/*.o $(EXECUTABLE) $(TESTS_EXECUTABLE)

install:
	@install -d $(DESTDIR)$(PREFIX)/bin
	@install -m755 $(EXECUTABLE) $(DESTDIR)$(PREFIX)/bin/$(EXECUTABLE)

uninstall:
	@rm -f $(PREFIX)/bin/$(EXECUTABLE)
