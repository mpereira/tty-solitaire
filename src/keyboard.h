#ifndef TTY_SOLITAIRE_KEYBOARD_H
#define TTY_SOLITAIRE_KEYBOARD_H

#include "deck.h"
#include "cursor.h"

#define KEY_SPACEBAR 32
#define KEY_ESCAPE 27

extern struct deck *deck;
extern struct cursor *cursor;

void keyboard_event();

#endif
