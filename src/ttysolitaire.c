#include <ncurses.h>
#include <locale.h>

#include "draw.h"
#include "game.h"
#include "keyboard.h"

const char *program_name;

int main(int argc, const char *argv[]) {
  program_name = *argv;

  setlocale(LC_ALL, "");            /* Support unicode characters.   */
  initscr();
  raw();                            /* Disable line buffers.         */
  noecho();
  keypad(stdscr, TRUE);             /* Give us keyboard key symbols. */
  start_color();
  curs_set(FALSE);                  /* We have our own cursor.       */
  set_escdelay(0);
  assume_default_colors(COLOR_WHITE, COLOR_GREEN);
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);

  draw_greeting();

  int key;
  do {
    switch (key = getch()) {
    case KEY_SPACEBAR:
      clear();
      refresh();
      game_init();
      break;
    case 'q':
    case 'Q':
      endwin();
      return(0);
    }
  } while (key != KEY_SPACEBAR);

  do {
    if ((key = getch()) == 'q' || key == 'Q') {
      endwin();
      game_end();
    } else {
      handle_keyboard_event(key);
    }
  } while (key != 'q' && key != 'Q');

  return(0);
}
