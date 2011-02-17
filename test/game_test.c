#include <assert.h>
#include "../lib/stack.h"
#include "../lib/game.h"
#include "test_helper.h"

void test_move_card_from_empty_stack_to_empty_stack() {
  struct stack *origin, *destination,
               *new_origin, *new_destination,
               *origin_duplicate, *destination_duplicate;

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  new_origin = origin;
  new_destination = destination;
  origin_duplicate = duplicate_stack(origin);
  destination_duplicate = duplicate_stack(destination);
  move_card(&new_origin, &new_destination);

  assert(origin == new_origin);
  assert(stacks_equal(origin, origin_duplicate));
  assert(destination == new_destination);
  assert(stacks_equal(destination, destination_duplicate));

  free_stack(origin);
  free_stack(destination);

  return;
}

void test_move_card_from_empty_stack_to_non_empty_stack() {
  struct stack *origin, *destination,
               *new_origin, *new_destination,
               *origin_duplicate, *destination_duplicate;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  new_origin = origin;
  new_destination = destination;
  push(&new_destination, card);
  origin_duplicate = duplicate_stack(origin);
  destination_duplicate = duplicate_stack(destination);
  move_card(&new_origin, &new_destination);

  assert(origin == new_origin);
  assert(stacks_equal(origin, origin_duplicate));
  assert(destination == new_destination);
  assert(stacks_equal(destination, destination_duplicate));

  free_stack(origin);
  free_stack(destination);

  return;
}

void test_move_card_from_non_empty_stack_to_empty_stack() {
  struct stack *origin, *destination;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  push(&origin, card);
  move_card(&origin, &destination);

  assert(empty(origin));
  assert(length(destination) == 1);
  assert(cards_equal(destination->card, card));

  free_stack(origin);
  free_stack(destination);

  return;
}

void test_move_card_from_non_empty_stack_to_non_empty_stack() {
  struct stack *origin, *destination;
  struct card *card[2];

  allocate_card(&card[0]);
  allocate_card(&card[1]);
  initialize_card(card[0]);
  initialize_card(card[1]);
  set_card(card[0], ACE, SPADES, EXPOSED, 1, 1);
  set_card(card[1], KING, HEARTS, EXPOSED, 1, 1);

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  push(&origin, card[0]);
  push(&destination, card[1]);
  move_card(&origin, &destination);

  assert(empty(origin));
  assert(length(destination) == 2);
  assert(cards_equal(destination->card, card[0]));
  assert(cards_equal(destination->next->card, card[1]));

  free_stack(origin);
  free_stack(destination);

  return;
}

void test_game() {
  test_move_card_from_empty_stack_to_empty_stack();
  test_move_card_from_empty_stack_to_non_empty_stack();
  test_move_card_from_non_empty_stack_to_empty_stack();
  test_move_card_from_non_empty_stack_to_non_empty_stack();

  return;
}
