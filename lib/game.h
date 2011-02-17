#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "cursor.h"

#define NUMBER_OF_CARDS 52

extern const char *program_name;
struct deck *deck;
struct cursor *cursor;

void move_card(struct stack **, struct stack **);
void greet_player();
void initialize_game();
void end_game();

#endif
