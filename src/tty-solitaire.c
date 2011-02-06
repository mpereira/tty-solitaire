#include <stdlib.h>
#include <curses.h>
#include "../lib/util.h"
#include "../lib/game.h"
#include "../lib/keyboard.h"

const char *program_name;

int main(int argc, const char *argv[]) {
  program_name = *argv;
  int key;

  initialize_curses();
  greet_player();

  while (key != KEY_SPACEBAR) {
    switch (key = getch()) {
    case KEY_SPACEBAR:
      initialize_game();
      break;
    case 'q':
    case 'Q':
      end_game();
      end_curses();
      exit(0);
    }
  }

  while (1) {
    if ((key = getch()) == 'q' || key == 'Q') {
      end_game();
      end_curses();
      exit(0);
    } else {
      handle_keyboard_event(key);
    }
  }

  return(0);
}
