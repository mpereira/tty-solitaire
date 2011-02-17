#ifndef STACK_H
#define STACK_H

#include "card.h"

#define MANEUVRE_STACKS_STARTING_Y 7

#define STOCK_STARTING_X        1
#define STOCK_STARTING_Y        1

#define WASTE_PILE_STARTING_X   9
#define WASTE_PILE_STARTING_Y   1

#define FOUNDATION_STARTING_Y   1
#define FOUNDATION_0_STARTING_X 25
#define FOUNDATION_1_STARTING_X 33
#define FOUNDATION_2_STARTING_X 41
#define FOUNDATION_3_STARTING_X 49

#define MANEUVRE_STARTING_Y     9
#define MANEUVRE_0_STARTING_X   1
#define MANEUVRE_1_STARTING_X   9
#define MANEUVRE_2_STARTING_X   17
#define MANEUVRE_3_STARTING_X   25
#define MANEUVRE_4_STARTING_X   33
#define MANEUVRE_5_STARTING_X   41
#define MANEUVRE_6_STARTING_X   49

struct stack {
  struct card  *card;
  struct stack *next;
};

extern const char *program_name;

void allocate_stack(struct stack **);
void initialize_stack(struct stack *);
void free_stack(struct stack *);
bool empty(struct stack *);
int length(struct stack *);
void push(struct stack **, struct card *);
struct stack *pop(struct stack **);

#endif
