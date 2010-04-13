#include "../lib/util.h"
#include "../lib/game.h"

int main(int argc, const char *argv[]) {
  initialize_curses();

  initialize_game();

  return(0);
}
