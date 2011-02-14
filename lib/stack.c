#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "stack.h"

static bool maneuvre_stack(struct stack *stack) {
  return(stack->card->frame->start_y >= MANEUVRE_STACKS_STARTING_Y);
}

void allocate_stack(struct stack **stack) {
  if (!(*stack = malloc(sizeof(**stack)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }

  allocate_card(&((*stack)->card));

  return;
}

void initialize_stack(struct stack *stack) {
  initialize_card(stack->card);
  stack->next = NULL;

  return;
}

void free_stack(struct stack *stack) {
  struct stack *tmp_stack;

  while (stack) {
    tmp_stack = stack->next;
    free_card(stack->card);
    free(stack);
    stack = tmp_stack;
  }

  return;
}

bool empty(struct stack *stack) {
  return(stack->card->value == NO_VALUE &&
         stack->card->suit == NO_SUIT &&
         stack->card->face == NO_FACE &&
         !stack->next);
}

int length(struct stack *stack) {
  struct stack *iterator = stack;
  int length = 0;

  if (!empty(stack)) {
    length = 1;
    while (iterator->next != NULL) {
      length++;
      iterator = iterator->next;
    }
  }

  return(length);
}

void push(struct stack **stack, struct card *card) {
  struct stack *new_stack = NULL;

  if (card) {
    if (empty(*stack)) {
      (*stack)->card = card;
    } else {
      allocate_stack(&new_stack);
      new_stack->card = card;
      new_stack->next = (*stack);
      *stack = new_stack;
    }
  }
}

struct stack *pop(struct stack **stack) {
  struct stack *popped_entry = NULL;

  if(!empty(*stack)) {
    popped_entry = *stack;
    /* As what's considered an empty stack is an allocated and initialized
     * stack structure, we make sure pop doesn't make '*stack' point to NULL
     * when popping a stack with only 1 element. */
    if (length(*stack) == 1) {
      allocate_stack(stack);
      initialize_stack(*stack);
      set_frame((*stack)->card->frame,
                (*stack)->card->frame->start_y,
                (*stack)->card->frame->start_x);
    } else {
      *stack = (*stack)->next;
    }
    popped_entry->next = NULL;
  }

  return(popped_entry);
}

void move_card(struct stack **origin, struct stack **destination) {
  struct stack *stack = NULL;

  (*origin)->card->frame->start_x = (*destination)->card->frame->start_x;
  (*origin)->card->frame->start_y = (*destination)->card->frame->start_y;
  if (!empty(*destination) && maneuvre_stack(*destination)) {
    (*origin)->card->frame->start_y++;
  }
  if ((stack = pop(origin))) {
    push(destination, stack->card);
  }

  return;
}
