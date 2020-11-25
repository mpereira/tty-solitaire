#include <assert.h>
#include <stdbool.h>
#include "../src/keyboard.h"
#include "../src/game.h"

void test_marked_count_empty_stack() {
  struct stack *empty;
  stack_malloc(&empty);
  stack_init(empty);

  assert(stack_empty(empty));
  assert(marked_cards_count(empty) == 0);

  stack_free(empty);
}

void test_marked_count_unmarked_stack() {
  struct stack *origin, *destination;

  stack_malloc(&origin);
  stack_init(origin);
  card_set(origin->card, ACE, DIAMONDS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);

  stack_malloc(&destination);
  stack_init(destination);
  card_set(destination->card, TWO, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);

  move_card(&origin, &destination);

  assert(marked_cards_count(destination) == 0);

  stack_free(origin);
  stack_free(destination);
}

void test_marked_count_marked_stack() {
  /* We need to create two stacks and use move_card from one to the other in
   * order to get the proper layout ie. next->begin_y = prev->begin_y + 1 */
  struct stack *origin[13], *destination;

  for (int i = 0; i < 13; i++) {
    stack_malloc(&origin[i]);
    stack_init(origin[i]);
  }
  card_set(origin[0]->card, ACE, DIAMONDS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[1]->card, TWO, CLUBS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[2]->card, THREE, HEARTS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[3]->card, FOUR, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[4]->card, FIVE, DIAMONDS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[5]->card, SIX, CLUBS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[6]->card, SEVEN, HEARTS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[7]->card, EIGHT, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[8]->card, NINE, DIAMONDS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[9]->card, TEN, CLUBS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[10]->card, JACK, HEARTS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[11]->card, QUEEN, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(origin[12]->card, KING, DIAMONDS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);

  stack_malloc(&destination);
  stack_init(destination);
  frame_set(destination->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);

  for (int i = 12; i >= 0 ; i--) {
    move_card(&origin[i], &destination);
  }

  struct stack *tmp = destination;
  for (int i = 0; tmp; i++, tmp = tmp->next) {
    card_mark(tmp->card);
    assert(marked_cards_count(destination) == i + 1);
  }

  for (int i = 0; i < 13; i++) {
    stack_free(origin[i]);
  }
  stack_free(destination);
}

void test_keyboard() {
  test_marked_count_empty_stack();
  test_marked_count_unmarked_stack();
  test_marked_count_marked_stack();
}
