#ifndef TTY_SOLITAIRE_DRAW_H
#define TTY_SOLITAIRE_DRAW_H

#include "card.h"
#include "stack.h"
#include "deck.h"
#include "cursor.h"

#define BLACK_ON_WHITE 1
#define RED_ON_WHITE   2
#define WHITE_ON_BLUE  3
#define WHITE_ON_GREEN 4

extern struct game game;

void draw_card(struct card *);
void draw_stack(struct stack *);
void draw_deck(struct deck *);
void draw_cursor(struct cursor *);
void erase_card(struct card *);
void erase_stack(struct stack *);
void erase_cursor(struct cursor *);

#endif
