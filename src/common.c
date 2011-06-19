#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "common.h"

bool term_size_ok() {
  int lines, columns;
  getmaxyx(stdscr, lines, columns);
  return(lines >= MIN_TERM_LINES && columns >= MIN_TERM_COLS);
}

void tty_solitaire_generic_error(int errno, char *file, int line) {
  char message[TTY_SOLITAIRE_BUFSIZ];
  snprintf(message,
           TTY_SOLITAIRE_BUFSIZ,
           "%s: %s (%s:%d)",
           program_name,
           strerror(errno),
           file,
           line - 1);
  fprintf(stderr, "%s\n", message);
  exit(errno);
}
