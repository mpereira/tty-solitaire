#ifndef TTY_SOLITAIRE_CURSOR_H
#define TTY_SOLITAIRE_CURSOR_H

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
  WINDOW *window;
  int x;
  int y;
  bool marked;
};

enum movement { LEFT, DOWN, UP, RIGHT };

extern struct deck *deck;
extern struct game game;

void cursor_malloc(struct cursor **);
void cursor_init(struct cursor *);
void cursor_free(struct cursor *);
void cursor_mark(struct cursor *);
void cursor_unmark(struct cursor *);
void cursor_move(struct cursor *, enum movement);
enum movement cursor_direction(int);
struct stack **cursor_stack(struct cursor *);
bool cursor_on_stock(struct cursor *);
bool cursor_on_invalid_spot(struct cursor *);

#endif
