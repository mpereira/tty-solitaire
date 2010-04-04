#ifndef STACK_H
#define STACK_H

struct stack {
  struct card  *card;
  struct stack *next;
};

#endif
