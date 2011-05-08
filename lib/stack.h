#ifndef STACK_H
#define STACK_H

#include "card.h"

struct stack {
  struct card  *card;
  struct stack *next;
};

void allocate_stack(struct stack **);
void initialize_stack(struct stack *);
struct stack *duplicate_stack(struct stack *);
void free_stack(struct stack *);
bool empty(struct stack *);
int length(struct stack *);
void push(struct stack **, struct card *);
struct stack *pop(struct stack **);
struct stack *reverse(struct stack *);

#endif
