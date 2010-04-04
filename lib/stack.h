#ifndef STACK_H
#define STACK_H

struct stack {
  struct card  *card;
  struct stack *next;
};

void initialize_stack(struct stack **);
bool empty(struct stack *);
int length(struct stack *);
void push(struct stack **, struct card *);
struct stack *pop(struct stack **);

#endif
