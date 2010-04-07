#ifndef DECK_H
#define DECK_H

#include "stack.h"

struct deck {
  struct stack *stock;

  struct stack *foundation_0;
  struct stack *foundation_1;
  struct stack *foundation_2;
  struct stack *foundation_3;

  struct stack *maneuvre_0;
  struct stack *maneuvre_1;
  struct stack *maneuvre_2;
  struct stack *maneuvre_3;
  struct stack *maneuvre_4;
  struct stack *maneuvre_5;
  struct stack *maneuvre_6;
};

void allocate_deck(struct deck **);
void initialize_deck(struct deck *);
void delete_deck(struct deck *);
void shuffle_deck(struct deck *);

#endif
