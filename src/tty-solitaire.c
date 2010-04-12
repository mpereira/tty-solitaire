#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include "../lib/display.h"

int main(int argc, const char *argv[]) {
  initialize_curses();

  initialize_game();

  return(0);
}
