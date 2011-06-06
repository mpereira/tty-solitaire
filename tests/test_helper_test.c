#include <assert.h>
#include "test_helper.h"

void test_frames_equal_with_two_nulls() {
  assert(frames_equal(NULL, NULL));
}

void test_frames_equal_with_one_null() {
  struct frame *frame;

  frame_malloc(&frame);
  assert(!frames_equal(frame, NULL));
  assert(!frames_equal(NULL, frame));
}

void test_frames_equal_with_two_equivalent_frames() {
  struct frame *frame_0, *frame_1;
  const int begin_y = 5, begin_x = 10;

  frame_malloc(&frame_0);
  frame_malloc(&frame_1);
  frame_set(frame_0, begin_y, begin_x);
  frame_set(frame_1, begin_y, begin_x);

  assert(frames_equal(frame_0, frame_1));
}

void test_frames_equal_with_two_frame_pointers_to_the_same_address() {
  struct frame *frame;

  frame_malloc(&frame);

  assert(frames_equal(frame, frame));
}

void test_cards_equal_with_two_nulls() {
  assert(cards_equal(NULL, NULL));
}

void test_cards_equal_with_one_null() {
  struct card *card;

  card_malloc(&card);
  assert(!cards_equal(card, NULL));
  assert(!cards_equal(NULL, card));
}

void test_cards_equal_with_two_equivalent_cards() {
  struct card *card_0, *card_1;
  const int begin_y = 5, begin_x = 10;

  card_malloc(&card_0);
  card_malloc(&card_1);
  card_set(card_0, ACE, SPADES, EXPOSED, begin_y, begin_x);
  card_set(card_1, ACE, SPADES, EXPOSED, begin_y, begin_x);

  assert(cards_equal(card_0, card_1));
}

void test_cards_equal_with_two_card_pointers_to_the_same_address() {
  struct card *card;

  card_malloc(&card);

  assert(cards_equal(card, card));
}

void test_stacks_equal_with_two_nulls() {
  assert(stacks_equal(NULL, NULL));
}

void test_stacks_equal_with_one_null() {
  struct stack *stack;

  stack_malloc(&stack);
  assert(!stacks_equal(stack, NULL));
  assert(!stacks_equal(NULL, stack));
}

void test_stacks_equal_with_two_equivalent_stacks() {
  struct stack *stack_0, *stack_1;
  struct card *card_0, *card_1;
  const int begin_y = 5, begin_x = 10;

  card_malloc(&card_0);
  card_malloc(&card_1);
  card_set(card_0, ACE, SPADES, EXPOSED, begin_y, begin_x);
  card_set(card_1, ACE, SPADES, EXPOSED, begin_y, begin_x);
  stack_malloc(&stack_0);
  stack_malloc(&stack_1);
  stack_push(&stack_0, card_0);
  stack_push(&stack_1, card_1);

  assert(stacks_equal(stack_0, stack_1));
}

void test_stacks_equal_with_two_different_stacks() {
  struct stack *stack_0, *stack_1;
  struct card *card_0, *card_1;
  const int begin_y = 5, begin_x = 10;

  card_malloc(&card_0);
  card_malloc(&card_1);
  card_set(card_0, ACE, SPADES, EXPOSED, begin_y, begin_x);
  card_set(card_1, KING, HEARTS, EXPOSED, begin_y, begin_x);
  stack_malloc(&stack_0);
  stack_malloc(&stack_1);
  stack_push(&stack_0, card_0);
  stack_push(&stack_1, card_1);

  assert(!stacks_equal(stack_0, stack_1));
}

void test_stacks_equal_with_two_stack_pointers_to_the_same_address() {
  struct stack *stack;

  stack_malloc(&stack);

  assert(stacks_equal(stack, stack));
}

void test_test_helper() {
  test_frames_equal_with_two_nulls();
  test_frames_equal_with_one_null();
  test_frames_equal_with_two_equivalent_frames();
  test_frames_equal_with_two_frame_pointers_to_the_same_address();

  test_cards_equal_with_two_nulls();
  test_cards_equal_with_two_equivalent_cards();
  test_cards_equal_with_two_card_pointers_to_the_same_address();

  test_stacks_equal_with_two_nulls();
  test_stacks_equal_with_one_null();
  test_stacks_equal_with_two_equivalent_stacks();
  test_stacks_equal_with_two_different_stacks();
  test_stacks_equal_with_two_stack_pointers_to_the_same_address();
}
