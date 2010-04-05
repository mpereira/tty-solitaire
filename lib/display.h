#ifndef DISPLAY_H
#define DISPLAY_H

#include "card.h"

#define DIAMONDS_SYMBOL "\u2666"
#define SPADES_SYMBOL   "\u2660"
#define HEARTS_SYMBOL   "\u2665"
#define CLUBS_SYMBOL    "\u2663"

#define BLACK_ON_WHITE 1
#define RED_ON_WHITE   2
#define WHITE_ON_BLUE  3

void init_curses();
char *card_suit(enum suit);
char *card_value(enum value);
void draw_value(struct card *);
void draw_suit(struct card *);
void draw_front(struct card *);
void draw_back(struct card *);
void draw_card(struct card *);

#endif
