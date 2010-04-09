#ifndef DISPLAY_H
#define DISPLAY_H

#include "card.h"

#define EMPTY_STACKS_NUMBER 13

#define DIAMONDS_SYMBOL "\u2666"
#define SPADES_SYMBOL   "\u2660"
#define HEARTS_SYMBOL   "\u2665"
#define CLUBS_SYMBOL    "\u2663"

#define BLACK_ON_WHITE 1
#define RED_ON_WHITE   2
#define WHITE_ON_BLUE  3

#define STOCK_STARTING_X        1
#define STOCK_STARTING_Y        1
#define WASTE_PILE_STARTING_X   9
#define WASTE_PILE_STARTING_Y   1
#define FOUNDATION_0_STARTING_X 25
#define FOUNDATION_0_STARTING_Y 1
#define FOUNDATION_1_STARTING_X 33
#define FOUNDATION_1_STARTING_Y 1
#define FOUNDATION_2_STARTING_X 41
#define FOUNDATION_2_STARTING_Y 1
#define FOUNDATION_3_STARTING_X 49
#define FOUNDATION_3_STARTING_Y 1
#define MANEUVRE_0_STARTING_X   1
#define MANEUVRE_0_STARTING_Y   7
#define MANEUVRE_1_STARTING_X   9
#define MANEUVRE_1_STARTING_Y   7
#define MANEUVRE_2_STARTING_X   17
#define MANEUVRE_2_STARTING_Y   7
#define MANEUVRE_3_STARTING_X   25
#define MANEUVRE_3_STARTING_Y   7
#define MANEUVRE_4_STARTING_X   33
#define MANEUVRE_4_STARTING_Y   7
#define MANEUVRE_5_STARTING_X   41
#define MANEUVRE_5_STARTING_Y   7
#define MANEUVRE_6_STARTING_X   49
#define MANEUVRE_6_STARTING_Y   7

void init_curses();
void draw_empty_stacks();
void initialize_game();
char *card_suit(enum suit);
char *card_value(enum value);
void draw_value(struct card *);
void draw_suit(struct card *);
void draw_front(struct card *);
void draw_back(struct card *);
void draw_card(struct card *);

#endif
