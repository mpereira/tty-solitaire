#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include "common.h"
#include "../lib/card.h"

int main(int argc, const char *argv[]) {
  char message[] = "Welcome to tty-solitaire.";
  int ch;
  int row_number, column_number;
  struct card *card = NULL;

  initscr();                /* initialize the terminal in curses mode */
  raw();                    /* disable line buffers                   */
  noecho();                 /* character echo is unnecessary          */
  keypad(stdscr, TRUE);     /* enable F and arrow keys                */

  getmaxyx(stdscr, row_number, column_number);
  mvprintw(row_number / 2 - 1,
           (column_number - strlen(message)) / 2,
           "%s\n",
           message);

  card = initialize_card();

  set_card(card, KING, CLUBS, TRUE, 1, 1);

  refresh_card(card);

  while ((ch = getch()) != KEY_F(1)) {
    switch(ch) {
      case KEY_LEFT:
      case 'h':
        refresh_card(card);
        break;
      case KEY_RIGHT:
      case 'l':
        refresh_card(card);
        break;
      case KEY_UP:
      case 'k':
        refresh_card(card);
        break;
      case KEY_DOWN:
      case 'j':
        refresh_card(card);
        break;
    }
  }

  endwin();
  puts("Game finished.");

  return 0;
}
