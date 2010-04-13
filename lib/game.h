#ifndef GAME_H
#define GAME_H

#include "deck.h"

#define NUMBER_OF_CARDS 52

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

void set_stacks_coordinates(struct deck *);
void fill_deck(struct deck *);
void shuffle_deck(struct deck *);
void deal_cards(struct deck *);
void greet_player();
void initialize_game();
void prepare_game(struct deck **);
void end_game();

#endif
