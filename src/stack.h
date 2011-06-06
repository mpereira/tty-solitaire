#ifndef TTY_SOLITAIRE_STACK_H
#define TTY_SOLITAIRE_STACK_H

#include "card.h"

struct stack {
  struct card  *card;
  struct stack *next;
};

void stack_malloc(struct stack **);
void stack_init(struct stack *);
void stack_free(struct stack *);
bool stack_empty(struct stack *);
int stack_length(struct stack *);
void stack_push(struct stack **, struct card *);
struct card *stack_pop(struct stack **);
struct stack *stack_reverse(struct stack *);
struct stack *stack_dup(struct stack *);

#endif
