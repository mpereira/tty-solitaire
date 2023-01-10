#ifndef TTY_SOLITAIRE_KEYBOARD_H
#define TTY_SOLITAIRE_KEYBOARD_H

#include "deck.h"
#include "cursor.h"

#define KEY_SPACEBAR 32
#define KEY_ESCAPE 277
#define KEY_F1 265
#define KEY_F2 266
#define KEY_F3 267
#define KEY_F4 268

extern struct deck *deck;
extern struct cursor *cursor;
extern struct game game;

void keyboard_event();

#endif
