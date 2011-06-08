#ifndef TTY_SOLITAIRE_GAME_H
#define TTY_SOLITAIRE_GAME_H

#include <stdbool.h>

#include "stack.h"
#include "deck.h"
#include "cursor.h"

#define NUMBER_OF_CARDS 52

#define STOCK_BEGIN_X        1
#define STOCK_BEGIN_Y        1

#define WASTE_PILE_BEGIN_X   9
#define WASTE_PILE_BEGIN_Y   1

#define FOUNDATION_BEGIN_Y   1
#define FOUNDATION_0_BEGIN_X 25
#define FOUNDATION_1_BEGIN_X 33
#define FOUNDATION_2_BEGIN_X 41
#define FOUNDATION_3_BEGIN_X 49

#define MANEUVRE_BEGIN_Y     9
#define MANEUVRE_0_BEGIN_X   1
#define MANEUVRE_1_BEGIN_X   9
#define MANEUVRE_2_BEGIN_X   17
#define MANEUVRE_3_BEGIN_X   25
#define MANEUVRE_4_BEGIN_X   33
#define MANEUVRE_5_BEGIN_X   41
#define MANEUVRE_6_BEGIN_X   49

struct game {
  int passes_through_deck_left;
};

struct deck *deck;
struct cursor *cursor;

bool maneuvre_stack(struct stack *);
bool stock_stack(struct stack *);
bool valid_move(struct stack *, struct stack *);
void move_card(struct stack **, struct stack **);
void move_block(struct stack **, struct stack **, int);
void game_init(struct game *, int);
bool game_won();
void game_end();

#endif
