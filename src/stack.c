#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "stack.h"
#include "card.h"
#include "common.h"

void stack_malloc(struct stack **stack) {
  if (!(*stack = malloc(sizeof(**stack)))) {
    tty_solitaire_generic_error(errno, __FILE__, __LINE__);
  }
  card_malloc(&((*stack)->card));
}

void stack_init(struct stack *stack) {
  card_init(stack->card);
  stack->next = NULL;
}

void stack_free(struct stack *stack) {
  struct stack *tmp;

  for (; stack; stack = tmp) {
    tmp = stack->next;
    card_free(stack->card);
    free(stack);
  }
}

struct stack *stack_dup(struct stack *stack) {
  struct stack *iterator = stack;
  struct stack *tmp_stack, *new_stack;

  stack_malloc(&new_stack);
  stack_malloc(&tmp_stack);
  stack_init(new_stack);
  stack_init(tmp_stack);
  for (iterator = stack; iterator; iterator = iterator->next) {
    stack_push(&tmp_stack, card_dup(iterator->card));
  }
  while (!stack_empty(tmp_stack)) {
    stack_push(&new_stack, (stack_pop(&tmp_stack)));
  }
  stack_free(tmp_stack);

  return(new_stack);
}

bool stack_empty(struct stack *stack) {
  return(stack->card->value == NO_VALUE &&
           stack->card->suit == NO_SUIT &&
           stack->card->face == NO_FACE &&
           !stack->next);
}

int stack_length(struct stack *stack) {
  int stack_length = 0;

  if (!stack_empty(stack)) {
    for (stack_length = 1; stack->next; stack = stack->next, stack_length++)
      ;
  }

  return(stack_length);
}

void stack_push(struct stack **stack, struct card *card) {
  if (card) {
    if (stack_empty(*stack)) {
      (*stack)->card = card;
    } else {
      /* Allocating by hand because stack_malloc() would
       * have allocated an unwanted card object. */
      struct stack *new_stack = malloc(sizeof(*new_stack));
      new_stack->card = card;
      new_stack->next = (*stack);
      *stack = new_stack;
    }
  }
}

struct card *stack_pop(struct stack **stack) {
  if(stack_empty(*stack)) {
    return(NULL);
  } else {
    struct card *popped_card = (*stack)->card;
    if (stack_length(*stack) == 1) {
      /* Remembering the stack position before clearing it. */
      int begin_y = (*stack)->card->frame->begin_y;
      int begin_x = (*stack)->card->frame->begin_x;
      card_malloc(&((*stack)->card));
      /* An stack_empty stack is a stack with a blank top card
       * and with stack->next == NULL. */
      card_set((*stack)->card, NO_VALUE, NO_SUIT, NO_FACE, begin_y, begin_x);
      (*stack)->next = NULL;
    } else {
      struct stack *tmp = *stack;
      *stack = (*stack)->next;
      free(tmp);
    }
    return(popped_card);
  }
}

struct stack *stack_reverse(struct stack *stack) {
  struct stack *tmp_stack, *iterator;

  stack_malloc(&tmp_stack);
  stack_init(tmp_stack);
  if (stack_length(stack) > 1) {
    for (iterator = stack; iterator; iterator = iterator->next) {
      stack_push(&tmp_stack, card_dup(iterator->card));
    }
  } else {
    card_set(tmp_stack->card,
             stack->card->value,
             stack->card->suit,
             stack->card->face,
             stack->card->frame->begin_y,
             stack->card->frame->begin_x);
  }
  return(tmp_stack);
}
