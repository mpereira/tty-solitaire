#ifndef STACK_H
#define STACK_H

#include "card.h"

#define MANEUVRE_STACKS_STARTING_Y 7

struct stack {
  struct card  *card;
  struct stack *next;
};

extern const char *program_name;

void allocate_stack(struct stack **);
void initialize_stack(struct stack *);
void delete_stack(struct stack *);
bool empty(struct stack *);
int length(struct stack *);
void push(struct stack **, struct card *);
struct stack *pop(struct stack **);
bool maneuvre_stack(struct stack *);
bool waste_pile_stack(struct stack *);
void refresh_card_coordinates(struct stack *, struct stack *);
void move_card(struct stack **, struct stack **);

#endif
