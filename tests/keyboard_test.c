#include <assert.h>
#include <stdbool.h>
#include "../src/keyboard.h"
#include "../src/game.h"

void test_marked_count_of_stack() {
  struct stack *origin, *destination;

  stack_malloc(&origin);
  stack_init(origin);
  card_set(origin->card, TWO, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);

  stack_malloc(&destination);
  stack_init(destination);
  card_set(destination->card, TWO, DIAMONDS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);

  move_card(&origin, &destination);

  struct stack *tmp = destination;
  for (int i = 0; tmp; i++, tmp = tmp->next) {
    // assert(marked_cards_count(destination) == i);
    card_mark(tmp->card);
    assert(marked_cards_count(destination) == i + 1);
  }

  stack_free(origin);
  stack_free(destination);
}

void test_keyboard() {
  test_marked_count_of_stack();
}
