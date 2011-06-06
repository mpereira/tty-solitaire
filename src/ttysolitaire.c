#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>

#include "draw.h"
#include "game.h"
#include "keyboard.h"

const char *program_name;

void draw_greeting() {
  mvprintw(8, 26, "Welcome to tty-solitaire.");
  mvprintw(10, 27, "Move with \u2190\u2191\u2192\u2193 or hjkl.");
  mvprintw(11, 19, "Use the space bar to mark and move cards.");
  mvprintw(12, 16, "After marking a card you can use m to increase ");
  mvprintw(13, 17, "and n to decrease the number of marked cards.");
  mvprintw(15, 19, "Press the space bar to play or q to quit.");
}

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
      exit(0);
    } else {
      handle_keyboard_event(key);
    }
  } while (!game_won());

  endwin();
  game_end();
  printf("You won.\n");

  return(0);
}
