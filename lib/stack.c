#include <malloc.h>
#include <stdbool.h>
#include "card.h"
#include "stack.h"

void initialize_stack(struct stack **stack) {
  *stack = malloc(sizeof(**stack));

  (*stack)->card = NULL;
  (*stack)->next = NULL;

  return;
}

bool empty(struct stack *stack) {
  return(stack->card == NULL);
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

  if (empty(*stack)) {
    (*stack)->card = card;
  } else {
    initialize_stack(&new_stack);
    new_stack->card = card;
    new_stack->next = (*stack);
    *stack = new_stack;
  }
}

/* FIXME: uglyness inside if statement */
struct stack *pop(struct stack **stack) {
  struct stack *popped_entry = NULL;

  if(!empty(*stack)) {
    popped_entry = *stack;
    if (length(*stack) == 1) {
      initialize_stack(stack);
    } else {
      *stack = (*stack)->next;
    }
    popped_entry->next = NULL;
  }

  return(popped_entry);
}
