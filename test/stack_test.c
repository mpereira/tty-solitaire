#include <assert.h>
#include "test_helper.h"
#include "../lib/stack.h"

void test_initialize_stack() {
  struct stack *stack;

  allocate_stack(&stack);
  initialize_stack(stack);

  assert(stack->card->value == NO_VALUE);
  assert(!stack->next);

  free_stack(stack);

  return;
}

void test_empty_on_empty_stack() {
  struct stack *stack;

  allocate_stack(&stack);
  initialize_stack(stack);

  assert(empty(stack));

  free_stack(stack);

  return;
}

void test_empty_on_non_empty_stack() {
  struct stack *stack;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&stack);
  initialize_stack(stack);
  push(&stack, card);

  assert(!empty(stack));

  free_stack(stack);

  return;
}

void test_length() {
  struct stack *stack;
  struct card *card[4];

  allocate_stack(&stack);
  initialize_stack(stack);

  assert(length(stack) == 0);

  for (int i = 0; i < 4; i++) {
    allocate_card(&card[i]);
    initialize_card(card[i]);
    set_card(card[i], i, SPADES, EXPOSED, 0, 0);
    push(&stack, card[i]);
    assert(length(stack) == i + 1);
  }

  free_stack(stack);

  return;
}

void test_push_on_empty_stack() {
  struct stack *stack;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&stack);
  initialize_stack(stack);
  push(&stack, card);

  assert(stack->card == card);
  assert(!stack->next);

  free_stack(stack);

  return;
}

void test_push_on_non_empty_stack() {
  struct stack *stack;
  struct card *card_0, *card_1;

  allocate_card(&card_0);
  allocate_card(&card_1);
  initialize_card(card_0);
  initialize_card(card_1);
  set_card(card_0, ACE, SPADES, EXPOSED, 0, 0);
  set_card(card_1, ACE, HEARTS, EXPOSED, 0, 0);

  allocate_stack(&stack);
  initialize_stack(stack);
  push(&stack, card_0);
  push(&stack, card_1);

  assert(stack->card == card_1);
  assert(stack->next->card == card_0);
  assert(!stack->next->next);

  free_stack(stack);

  return;
}

void test_push_null_on_empty_stack() {
  struct stack *stack, *old_stack;

  allocate_stack(&stack);
  initialize_stack(stack);
  old_stack = stack;
  push(&stack, NULL);

  assert(stack->card == old_stack->card);
  assert(stack->next == NULL);

  free_stack(stack);

  return;
}

void test_push_null_on_non_empty_stack() {
  struct stack *stack, *old_stack;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&stack);
  initialize_stack(stack);
  old_stack = stack;
  push(&stack, NULL);

  assert(stack->card == old_stack->card);
  assert(stack->next == old_stack->next);

  free_stack(stack);

  return;
}

void test_pop_on_empty_stack() {
  struct stack *stack;
  struct stack *popped_entry;

  allocate_stack(&stack);
  allocate_stack(&popped_entry);
  initialize_stack(stack);
  popped_entry = pop(&stack);

  assert(empty(stack));
  assert(!popped_entry);

  free_stack(stack);

  return;
}

void test_pop_on_stack_with_one_element() {
  struct stack *stack, *popped_entry;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&stack);
  initialize_stack(stack);
  push(&stack, card);
  popped_entry = pop(&stack);

  assert(empty(stack));
  assert(popped_entry->card == card);
  assert(!popped_entry->next);

  free_stack(stack);

  return;
}

void test_pop_on_stack_with_more_than_one_element() {
  struct stack *stack, *old_stack_next, *popped_entry;
  struct card *card[3];

  allocate_stack(&stack);
  initialize_stack(stack);
  for (int i = 0; i < 3; i++) {
    allocate_card(&card[i]);
    initialize_card(card[i]);
    set_card(card[i], ACE, SPADES, EXPOSED, 0, 0);
    push(&stack, card[i]);
  }
  old_stack_next = stack->next;
  popped_entry = pop(&stack);

  assert(length(stack) == 2);
  assert(stack == old_stack_next);
  assert(popped_entry->card == card[2]);
  assert(!popped_entry->next);

  free_stack(stack);

  return;
}

void test_reverse_on_empty_stack() {
  struct stack *stack, *old_stack, *reversed_stack;

  allocate_stack(&stack);
  initialize_stack(stack);
  old_stack = stack;
  reversed_stack = reverse(&stack);

  assert(reversed_stack == old_stack);

  free_stack(stack);
}

void test_reverse_on_stack_with_one_element() {
  struct stack *stack, *old_stack, *reversed_stack;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&stack);
  initialize_stack(stack);
  push(&stack, card);
  old_stack = stack;
  reversed_stack = reverse(&stack);

  assert(reversed_stack == old_stack);

  free_stack(stack);
}

void test_reverse_on_stack_with_more_than_one_element() {
  struct stack *stack, *old_stack, *reversed_stack, *unreversed_stack;
  struct card *card[3];

  allocate_stack(&stack);
  initialize_stack(stack);
  for (int i = 0; i < 3; i++) {
    allocate_card(&card[i]);
    initialize_card(card[i]);
    set_card(card[i], TWO + i, DIAMONDS + i, EXPOSED, 0, 0);
    push(&stack, card[i]);
  }
  old_stack = duplicate_stack(stack);
  reversed_stack = reverse(&stack);

  allocate_stack(&unreversed_stack);
  initialize_stack(unreversed_stack);
  for (int i = 0; i < 3; i++) {
    push(&unreversed_stack, pop(&reversed_stack)->card);
  }

  assert(stacks_equal(unreversed_stack, old_stack));

  free_stack(reversed_stack);
  free_stack(stack);
}

void test_stack() {
  test_initialize_stack();

  test_empty_on_empty_stack();
  test_empty_on_non_empty_stack();

  test_length();

  test_push_on_empty_stack();
  test_push_on_non_empty_stack();
  test_push_null_on_empty_stack();

  test_pop_on_empty_stack();
  test_pop_on_stack_with_one_element();
  test_pop_on_stack_with_more_than_one_element();

  test_reverse_on_empty_stack();
  test_reverse_on_stack_with_one_element();
  test_reverse_on_stack_with_more_than_one_element();

  return;
}
