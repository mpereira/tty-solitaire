#include <ncurses.h>
#include <locale.h>

#include "game.h"
#include "keyboard.h"

const char *program_name;

int main(int argc, const char *argv[]) {
  program_name = *argv;
  int key;

  setlocale(LC_ALL, "en_US.utf-8"); /* Support unicode characters. */
  initscr();
  raw();                            /* Disable line buffers.       */
  noecho();
  keypad(stdscr, TRUE);             /* Enable arrow keys.          */
  start_color();                    /* I want colors.              */
  curs_set(FALSE);                  /* Invisible cursor.           */
  set_escdelay(0);
  assume_default_colors(COLOR_WHITE, COLOR_GREEN);
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);

  greet_player();

  while (key != KEY_SPACEBAR) {
    switch (key = getch()) {
    case KEY_SPACEBAR:
      initialize_game();
      break;
    case 'q':
    case 'Q':
      endwin();
      return(0);
    }
  }

  while (1) {
    if ((key = getch()) == 'q' || key == 'Q') {
      endwin();
      end_game();
      return(0);
    } else {
      handle_keyboard_event(key);
    }
  }

  return(0);
}
