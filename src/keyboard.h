#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "deck.h"
#include "cursor.h"

#define KEY_SPACEBAR 32
#define KEY_ESCAPE 27

extern struct deck *deck;
extern struct cursor *cursor;

void handle_keyboard_event();

#endif
