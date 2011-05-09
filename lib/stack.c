#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "stack.h"
#include "common.h"

void allocate_stack(struct stack **stack) {
  if (!(*stack = malloc(sizeof(**stack)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }

  allocate_card(&((*stack)->card));
}

void initialize_stack(struct stack *stack) {
  initialize_card(stack->card);
  stack->next = NULL;
}

struct stack *duplicate_stack(struct stack *stack) {
  struct stack *iterator = stack;
  struct stack *tmp_stack, *new_stack;

  allocate_stack(&new_stack);
  allocate_stack(&tmp_stack);
  initialize_stack(new_stack);
  initialize_stack(tmp_stack);
  for (iterator = stack; iterator; iterator = iterator->next) {
    push(&tmp_stack, duplicate_card(iterator->card));
  }
  while (!empty(tmp_stack)) {
    push(&new_stack, (pop(&tmp_stack))->card);
  }
  free_stack(tmp_stack);

  return(new_stack);
}

void free_stack(struct stack *stack) {
  struct stack *tmp;

  for (; stack; stack = tmp) {
    tmp = stack->next;
    free_card(stack->card);
    free(stack);
  }
}

bool empty(struct stack *stack) {
  return(stack->card->value == NO_VALUE &&
         stack->card->suit == NO_SUIT &&
         stack->card->face == NO_FACE &&
         !stack->next);
}

int length(struct stack *stack) {
  int length = 0;

  if (!empty(stack)) {
    for (length = 1; stack->next; stack = stack->next, length++)
      ;
  }

  return(length);
}

void push(struct stack **stack, struct card *card) {
  struct stack *new_stack;

  if (card) {
    if (empty(*stack)) {
      (*stack)->card = duplicate_card(card);
    } else {
      allocate_stack(&new_stack);
      new_stack->card = duplicate_card(card);
      new_stack->next = (*stack);
      *stack = new_stack;
    }
  }
}

struct stack *pop(struct stack **stack) {
  struct stack *popped_entry = NULL;

  if(!empty(*stack)) {
    allocate_stack(&popped_entry);
    initialize_stack(popped_entry);
    popped_entry->card = duplicate_card((*stack)->card);
    popped_entry->next = NULL;
    if (length(*stack) == 1) {
      /* An empty stack is a stack with a blank top card
       * and with stack->next == NULL. */
      set_card((*stack)->card,
               NO_VALUE,
               NO_SUIT,
               NO_FACE,
               (*stack)->card->frame->begin_y,
               (*stack)->card->frame->begin_x);
      (*stack)->next = NULL;
    } else {
      *stack = (*stack)->next;
    }
  }

  return(popped_entry);
}

struct stack *reverse(struct stack *stack) {
  if (length(stack) > 1) {
    struct stack *tmp_stack, *iterator;

    allocate_stack(&tmp_stack);
    initialize_stack(tmp_stack);
    for (iterator = stack; iterator; iterator = iterator->next) {
      push(&tmp_stack, iterator->card);
    }
    return(tmp_stack);
  } else {
    return(stack);
  }
}
