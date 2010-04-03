#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include "common.h"
#include "../lib/card.h"

int main(int argc, const char *argv[]) {
  char message[] = "Welcome to tty-solitaire.";
  int row_number, column_number;

  setlocale(LC_ALL, "");    /* supporting unicode characters */
  initscr();                /* initialize the terminal in curses mode */
  raw();                    /* disable line buffers                   */
  noecho();                 /* character echo is unnecessary          */
  keypad(stdscr, TRUE);     /* enable F and arrow keys                */

  getmaxyx(stdscr, row_number, column_number);
  mvprintw(row_number / 2 - 1,
           (column_number - strlen(message)) / 2,
           "%s\n",
           message);
  getch();

  endwin();

  puts("Game finished.");

  return 0;
}
