#ifndef TTY_SOLITAIRE_KEYBOARD_H
#define TTY_SOLITAIRE_KEYBOARD_H

#include "deck.h"
#include "cursor.h"

#define KEY_SPACEBAR 32
#define KEY_ESCAPE 27

extern struct deck *deck;
extern struct cursor *cursor;
extern struct game game;

int marked_cards_count(struct stack *);
void keyboard_event();

#endif
