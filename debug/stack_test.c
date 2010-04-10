#include <stdio.h>
#include "stack_test.h"

void print_stack(struct stack *stack) {
  if (empty(stack)) {
    printf("Empty stack\n");
  } else {
    struct stack *iterator = stack;
    while (iterator != NULL) {
      print_card(iterator->card);
      iterator = iterator->next;
    }
  }

  return;
}
