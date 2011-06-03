#include "ttysolitaire_test.h"

const char *program_name;

int main(int argc, const char *argv[]) {
  program_name = argv[0];

  test_card();
  test_cursor();
  test_deck();
  test_display();
  test_frame();
  test_game();
  test_keyboard();
  test_stack();
  test_test_helper();

  return(0);
}
