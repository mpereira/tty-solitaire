#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include "../lib/display.h"

int main(int argc, const char *argv[]) {
  char message[] = "Welcome to tty-solitaire.";
  int row_number, column_number;

  init_curses();

  getmaxyx(stdscr, row_number, column_number);
  mvprintw(row_number / 2 - 1,
           (column_number - strlen(message)) / 2,
           "%s\n",
           message);
  getch();

  initialize_game();

  puts("Game finished.");

  return 0;
}
