#ifndef DECK_H
#define DECK_H

#include "stack.h"

enum stack_name {
  STOCK,
  WASTE_PILE,
  FOUNDATION_0,
  FOUNDATION_1,
  FOUNDATION_2,
  FOUNDATION_3,
  MANEUVRE_0,
  MANEUVRE_1,
  MANEUVRE_2,
  MANEUVRE_3,
  MANEUVRE_4,
  MANEUVRE_5,
  MANEUVRE_6
};

struct deck {
  struct stack *stock;
  struct stack *waste_pile;

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

extern const char *program_name;

void allocate_deck(struct deck **);
void initialize_deck(struct deck *);
void delete_deck(struct deck *);

#endif
