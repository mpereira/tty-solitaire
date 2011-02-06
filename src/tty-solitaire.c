#include <stdlib.h>
#include "../lib/util.h"
#include "../lib/game.h"
#include "../lib/cursor.h"
#include "../lib/keyboard.h"

extern struct deck *deck;
extern struct cursor *cursor;

int main(int argc, const char *argv[]) {
  int option;

  initialize_curses();
  greet_player();

  while (option != KEY_SPACEBAR) {
    switch (option = getch()) {
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
    switch (option = getch()) {
      case 'h':
      case KEY_LEFT:
        move_cursor(cursor, LEFT);
        break;
      case 'j':
      case KEY_DOWN:
        move_cursor(cursor, DOWN);
        break;
      case 'k':
      case KEY_UP:
        move_cursor(cursor, UP);
        break;
      case 'l':
      case KEY_RIGHT:
        move_cursor(cursor, RIGHT);
        break;
      case KEY_SPACEBAR:
        if (cursor_on_stock(cursor)) {
          handle_stock_event();
        } else {
          handle_card_movement(cursor);
        }
        break;
      case 'q':
      case 'Q':
        end_curses();
        print_deck(deck);
        exit(0);
    }
  }

  return(0);
}
