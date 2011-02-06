#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

void initialize_curses() {
  setlocale(LC_ALL, "en_US.utf-8");  /* supporting unicode characters          */
  initscr();                         /* initialize the terminal in curses mode */
  raw();                             /* disable line buffers                   */
  noecho();                          /* character echo is unnecessary          */
  keypad(stdscr, TRUE);              /* enable F and arrow keys                */
  start_color();                     /* I want colors                          */
  curs_set(FALSE);                   /* invisible cursor                       */
  assume_default_colors(COLOR_WHITE, COLOR_GREEN);

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);

  return;
}

void end_curses() {
  endwin();
  puts("Game finished.");

  return;
}

void clear_screen() {
  clear();
  refresh();

  return;
}
