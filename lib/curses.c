#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include "curses.h"

void initialize_curses() {
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
}

void end_curses() {
  endwin();
  puts("Game finished.");
}

void clear_screen() {
  clear();
  refresh();
}
