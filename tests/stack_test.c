#include <assert.h>
#include "test_helper.h"
#include "../src/stack.h"

void test_stack_init() {
  struct stack *stack;

  stack_malloc(&stack);
  stack_init(stack);

  assert(stack->card->value == NO_VALUE);
  assert(!stack->next);

  stack_free(stack);
}

void test_stack_dup() {
  struct stack *stack_0, *stack_1;
  struct card *card[5];
  const int begin_y = 5, begin_x = 10;

  stack_malloc(&stack_0);
  stack_init(stack_0);
  for (int i = 0; i < 5; i++) {
    card_malloc(&card[i]);
    card_set(card[i], i, SPADES, EXPOSED, begin_y, begin_x);
    stack_push(&stack_0, card[i]);
  }
  stack_1 = stack_dup(stack_0);

  assert(stack_0 != stack_1);
  assert(stacks_equal(stack_0, stack_1));
}

void test_stack_empty_on_stack_empty_stack() {
  struct stack *stack;

  stack_malloc(&stack);
  stack_init(stack);

  assert(stack_empty(stack));

  stack_free(stack);
}

void test_stack_empty_on_non_stack_empty_stack() {
  struct stack *stack;
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, 0, 0);

  stack_malloc(&stack);
  stack_init(stack);
  stack_push(&stack, card);

  assert(!stack_empty(stack));

  stack_free(stack);
}

void test_stack_length() {
  struct stack *stack;
  struct card *card[4];

  stack_malloc(&stack);
  stack_init(stack);

  assert(stack_length(stack) == 0);

  for (int i = 0; i < 4; i++) {
    card_malloc(&card[i]);
    card_init(card[i]);
    card_set(card[i], i, SPADES, EXPOSED, 0, 0);
    stack_push(&stack, card[i]);
    assert(stack_length(stack) == i + 1);
  }

  stack_free(stack);
}

void test_stack_push_on_stack_empty_stack() {
  struct stack *stack;
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, 0, 0);

  stack_malloc(&stack);
  stack_init(stack);
  stack_push(&stack, card);

  assert(cards_equal(stack->card, card));
  assert(!stack->next);

  stack_free(stack);
}

void test_stack_push_on_non_stack_empty_stack() {
  struct stack *stack;
  struct card *card_0, *card_1;

  card_malloc(&card_0);
  card_malloc(&card_1);
  card_init(card_0);
  card_init(card_1);
  card_set(card_0, ACE, SPADES, EXPOSED, 0, 0);
  card_set(card_1, ACE, HEARTS, EXPOSED, 0, 0);

  stack_malloc(&stack);
  stack_init(stack);
  stack_push(&stack, card_0);
  stack_push(&stack, card_1);

  assert(cards_equal(stack->card, card_1));
  assert(cards_equal(stack->next->card, card_0));
  assert(!stack->next->next);

  stack_free(stack);
}

void test_stack_push_null_on_stack_empty_stack() {
  struct stack *stack, *old_stack;

  stack_malloc(&stack);
  stack_init(stack);
  old_stack = stack;
  stack_push(&stack, NULL);

  assert(cards_equal(stack->card, old_stack->card));
  assert(!stack->next);

  stack_free(stack);
}

void test_stack_push_null_on_non_stack_empty_stack() {
  struct stack *stack, *old_stack;
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, 0, 0);

  stack_malloc(&stack);
  stack_init(stack);
  old_stack = stack_dup(stack);
  stack_push(&stack, NULL);

  assert(cards_equal(stack->card, old_stack->card));
  assert(stacks_equal(stack->next, old_stack->next));

  stack_free(stack);
}

void test_stack_pop_on_stack_empty_stack() {
  struct stack *stack;
  struct card *stack_popped_card;

  stack_malloc(&stack);
  stack_init(stack);
  stack_popped_card = stack_pop(&stack);

  assert(stack_empty(stack));
  assert(!stack_popped_card);

  stack_free(stack);
}

void test_stack_pop_on_stack_with_one_element() {
  struct stack *stack;
  struct card *card, *stack_popped_card;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, 0, 0);

  stack_malloc(&stack);
  stack_init(stack);
  stack_push(&stack, card);
  stack_popped_card = stack_pop(&stack);

  assert(stack_empty(stack));
  assert(stack_popped_card == card);

  stack_free(stack);
}

void test_stack_pop_on_stack_with_more_than_one_element() {
  struct stack *stack, *old_stack_next;
  struct card *card[3], *stack_popped_card;

  stack_malloc(&stack);
  stack_init(stack);
  for (int i = 0; i < 3; i++) {
    card_malloc(&card[i]);
    card_init(card[i]);
    card_set(card[i], ACE, SPADES, EXPOSED, 0, 0);
    stack_push(&stack, card[i]);
  }
  old_stack_next = stack->next;
  stack_popped_card = stack_pop(&stack);

  assert(stack_length(stack) == 2);
  assert(stack == old_stack_next);
  assert(stack_popped_card == card[2]);

  stack_free(stack);
}

void test_stack_reverse_on_stack_empty_stack() {
  struct stack *stack, *old_stack, *stack_reversed_stack;

  stack_malloc(&stack);
  stack_init(stack);
  old_stack = stack;
  stack_reversed_stack = stack_reverse(stack);

  assert(stacks_equal(stack_reversed_stack, old_stack));

  stack_free(stack);
}

void test_stack_reverse_on_stack_with_one_element() {
  struct stack *stack, *old_stack, *stack_reversed_stack;
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, 0, 0);

  stack_malloc(&stack);
  stack_init(stack);
  stack_push(&stack, card);
  old_stack = stack;
  stack_reversed_stack = stack_reverse(stack);

  assert(stacks_equal(stack_reversed_stack, old_stack));

  stack_free(stack);
}

void test_stack_reverse_on_stack_with_more_than_one_element() {
  struct stack *stack, *old_stack, *stack_reversed_stack, *unstack_reversed_stack;
  struct card *card[3];

  stack_malloc(&stack);
  stack_init(stack);
  for (int i = 0; i < 3; i++) {
    card_malloc(&card[i]);
    card_init(card[i]);
    card_set(card[i], TWO + i, DIAMONDS + i, EXPOSED, 0, 0);
    stack_push(&stack, card[i]);
  }
  old_stack = stack_dup(stack);
  stack_reversed_stack = stack_reverse(stack);

  stack_malloc(&unstack_reversed_stack);
  stack_init(unstack_reversed_stack);
  for (int i = 0; i < 3; i++) {
    stack_push(&unstack_reversed_stack, stack_pop(&stack_reversed_stack));
  }

  assert(stacks_equal(unstack_reversed_stack, old_stack));

  stack_free(stack_reversed_stack);
  stack_free(stack);
}

void test_stack_reverse_should_not_change_stack() {
  struct stack *stack, *old_stack, *old_stack_address;
  struct card *card[3];

  stack_malloc(&stack);
  stack_init(stack);
  for (int i = 0; i < 3; i++) {
    card_malloc(&card[i]);
    card_init(card[i]);
    card_set(card[i], TWO + i, DIAMONDS + i, EXPOSED, 0, 0);
    stack_push(&stack, card[i]);
  }
  old_stack_address = stack;
  old_stack = stack_dup(stack);
  stack_reverse(stack);

  assert(stack == old_stack_address);
  assert(stacks_equal(stack, old_stack));

  stack_free(stack);
}

void test_stack() {
  test_stack_init();

  test_stack_dup();

  test_stack_empty_on_stack_empty_stack();
  test_stack_empty_on_non_stack_empty_stack();

  test_stack_length();

  test_stack_push_on_stack_empty_stack();
  test_stack_push_on_non_stack_empty_stack();
  test_stack_push_null_on_stack_empty_stack();

  test_stack_pop_on_stack_empty_stack();
  test_stack_pop_on_stack_with_one_element();
  test_stack_pop_on_stack_with_more_than_one_element();

  test_stack_reverse_on_stack_empty_stack();
  test_stack_reverse_on_stack_with_one_element();
  test_stack_reverse_on_stack_with_more_than_one_element();
  test_stack_reverse_should_not_change_stack();
}
