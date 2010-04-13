#include <stdlib.h>
#include "../lib/util.h"
#include "../lib/game.h"
#include "../lib/keyboard.h"

int main(int argc, const char *argv[]) {
  int option;

  initialize_curses();

  greet_player();

  while (1) {
    switch (option = getch()) {
      case KEY_SPACEBAR:
        initialize_game();
        break;
      case 'q':
      case 'Q':
        end_curses();
        exit(0);
    }
  }

  while (1) {
    key_event();
  }

  return(0);
}
