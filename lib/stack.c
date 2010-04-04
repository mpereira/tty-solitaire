#include <malloc.h>
#include <stdbool.h>
#include "card.h"
#include "stack.h"

struct stack *initialize_stack() {
  struct stack *stack = NULL;

  stack = malloc(sizeof(stack));

  stack->card  = NULL;
  stack->next = NULL;

  return(stack);
}

bool empty(struct stack *stack) {
  return(stack->card == NULL);
}

int length(struct stack *stack) {
  int length = 0;

  if (!empty(stack)) {
    length = 1;
    while (stack->next != NULL) {
      length++;
    }
  }

  return(length);
}

void push(struct stack *stack, struct card *card) {
  struct stack *new_stack = NULL;

  if (empty(stack)) {
    stack->card = card;
  } else {
    new_stack = malloc(sizeof(new_stack));
    new_stack->card = card;
    new_stack->next = stack;
    stack = new_stack;
  }
}
