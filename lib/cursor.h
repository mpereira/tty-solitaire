#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>
#include "deck.h"

#define CURSOR_BEGIN_X 4
#define CURSOR_BEGIN_Y 7

#define CURSOR_INVALID_SPOT_X 20
#define CURSOR_INVALID_SPOT_Y 7

#define CURSOR_STOCK_X        4
#define CURSOR_WASTE_PILE_X   12
#define CURSOR_FOUNDATION_0_X 28
#define CURSOR_FOUNDATION_1_X 36
#define CURSOR_FOUNDATION_2_X 44
#define CURSOR_FOUNDATION_3_X 52
#define CURSOR_MANEUVRE_0_X   4
#define CURSOR_MANEUVRE_1_X   12
#define CURSOR_MANEUVRE_2_X   20
#define CURSOR_MANEUVRE_3_X   28
#define CURSOR_MANEUVRE_4_X   36
#define CURSOR_MANEUVRE_5_X   44
#define CURSOR_MANEUVRE_6_X   52

struct cursor {
  int x;
  int y;
};

enum movement { LEFT, DOWN, UP, RIGHT };

extern struct deck *deck;

void allocate_cursor(struct cursor **);
void initialize_cursor(struct cursor *);
void move_cursor(struct cursor *, enum movement);

#endif
