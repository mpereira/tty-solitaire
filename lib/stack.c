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
    push(&new_stack, (pop(&tmp_stack)));
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
  if (card) {
    if (empty(*stack)) {
      (*stack)->card = card;
    } else {
      struct stack *new_stack;
      allocate_stack(&new_stack);
      new_stack->card = card;
      new_stack->next = (*stack);
      *stack = new_stack;
    }
  }
}

struct card *pop(struct stack **stack) {
  if(empty(*stack)) {
    return(NULL);
  } else {
    struct card *popped_card = (*stack)->card;
    if (length(*stack) == 1) {
      /* Remembering the stack position before clearing it. */
      int begin_y = (*stack)->card->frame->begin_y;
      int begin_x = (*stack)->card->frame->begin_x;
      allocate_card(&((*stack)->card));
      /* An empty stack is a stack with a blank top card
       * and with stack->next == NULL. */
      set_card((*stack)->card, NO_VALUE, NO_SUIT, NO_FACE, begin_y, begin_x);
      (*stack)->next = NULL;
    } else {
      struct stack *tmp = *stack;
      *stack = (*stack)->next;
      free(tmp);
    }
    return(popped_card);
  }
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
