#include "ttysolitaire_test.h"
#include "../src/game.h"

const char *program_name;
struct game game;

int main(int argc, const char *argv[]) {
  program_name = argv[0];

  (void) argc;

  test_card();
  test_cursor();
  test_deck();
  test_gui();
  test_frame();
  test_game();
  test_keyboard();
  test_stack();
  test_test_helper();

  return(0);
}
