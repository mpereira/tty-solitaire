#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "deck.h"

#define KEY_SPACEBAR ' '

extern struct deck *deck;

void handle_stock_event();
int key_event();

#endif
