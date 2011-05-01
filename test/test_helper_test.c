#include <assert.h>
#include "test_helper.h"

void test_frames_equal_with_two_nulls() {
  assert(frames_equal(NULL, NULL));

  return;
}

void test_frames_equal_with_one_null() {
  struct frame *frame;

  allocate_frame(&frame);
  assert(!frames_equal(frame, NULL));
  assert(!frames_equal(NULL, frame));

  return;
}

void test_frames_equal_with_two_equivalent_frames() {
  struct frame *frame_0, *frame_1;
  const int start_y = 5, start_x = 10;

  allocate_frame(&frame_0);
  allocate_frame(&frame_1);
  set_frame(frame_0, start_y, start_x);
  set_frame(frame_1, start_y, start_x);

  assert(frames_equal(frame_0, frame_1));

  return;
}

void test_frames_equal_with_two_frame_pointers_to_the_same_address() {
  struct frame *frame;

  allocate_frame(&frame);

  assert(frames_equal(frame, frame));

  return;
}

void test_cards_equal_with_two_nulls() {
  assert(cards_equal(NULL, NULL));

  return;
}

void test_cards_equal_with_one_null() {
  struct card *card;

  allocate_card(&card);
  assert(!cards_equal(card, NULL));
  assert(!cards_equal(NULL, card));

  return;
}

void test_cards_equal_with_two_equivalent_cards() {
  struct card *card_0, *card_1;
  const int start_y = 5, start_x = 10;

  allocate_card(&card_0);
  allocate_card(&card_1);
  set_card(card_0, ACE, SPADES, EXPOSED, start_y, start_x);
  set_card(card_1, ACE, SPADES, EXPOSED, start_y, start_x);

  assert(cards_equal(card_0, card_1));

  return;
}

void test_cards_equal_with_two_card_pointers_to_the_same_address() {
  struct card *card;

  allocate_card(&card);

  assert(cards_equal(card, card));

  return;
}

void test_stacks_equal_with_two_nulls() {
  assert(stacks_equal(NULL, NULL));

  return;
}

void test_stacks_equal_with_one_null() {
  struct stack *stack;

  allocate_stack(&stack);
  assert(!stacks_equal(stack, NULL));
  assert(!stacks_equal(NULL, stack));

  return;
}

void test_stacks_equal_with_two_equivalent_stacks() {
  struct stack *stack_0, *stack_1;
  struct card *card_0, *card_1;
  const int start_y = 5, start_x = 10;

  allocate_card(&card_0);
  allocate_card(&card_1);
  set_card(card_0, ACE, SPADES, EXPOSED, start_y, start_x);
  set_card(card_1, ACE, SPADES, EXPOSED, start_y, start_x);
  allocate_stack(&stack_0);
  allocate_stack(&stack_1);
  push(&stack_0, card_0);
  push(&stack_1, card_1);

  assert(stacks_equal(stack_0, stack_1));

  return;
}

void test_stacks_equal_with_two_different_stacks() {
  struct stack *stack_0, *stack_1;
  struct card *card_0, *card_1;
  const int start_y = 5, start_x = 10;

  allocate_card(&card_0);
  allocate_card(&card_1);
  set_card(card_0, ACE, SPADES, EXPOSED, start_y, start_x);
  set_card(card_1, KING, HEARTS, EXPOSED, start_y, start_x);
  allocate_stack(&stack_0);
  allocate_stack(&stack_1);
  push(&stack_0, card_0);
  push(&stack_1, card_1);

  assert(!stacks_equal(stack_0, stack_1));

  return;
}

void test_stacks_equal_with_two_stack_pointers_to_the_same_address() {
  struct stack *stack;

  allocate_stack(&stack);

  assert(stacks_equal(stack, stack));

  return;
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

  return;
}
