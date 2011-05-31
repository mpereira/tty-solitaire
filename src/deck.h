#ifndef DECK_H
#define DECK_H

#include "stack.h"

struct deck {
  struct stack *stock;
  struct stack *waste_pile;
  struct stack *foundation[4];
  struct stack *maneuvre[7];
};

void allocate_deck(struct deck **);
void initialize_deck(struct deck *);
void free_deck(struct deck *);

#endif
