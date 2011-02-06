#ifndef GAME_H
#define GAME_H

#include "stack.h"
#include "deck.h"
#include "cursor.h"

#define NUMBER_OF_CARDS 52

extern const char *program_name;
struct deck *deck;
struct cursor *cursor;

void set_stacks_initial_coordinates(struct deck *);
void fill_deck(struct deck *);
void shuffle_deck(struct deck *);
void deal_cards(struct deck *);
void greet_player();
void initialize_game();
void end_game();

#endif
