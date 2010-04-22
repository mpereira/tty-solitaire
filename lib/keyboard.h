#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "deck.h"
#include "cursor.h"

#define KEY_SPACEBAR ' '

extern struct deck *deck;

void mark_origin(struct cursor *);
struct stack *cursor_stack(struct cursor *);
bool cursor_on_stack(struct cursor *, struct stack *);
void handle_stock_event();
void handle_card_movement(struct cursor *);
int key_event();

#endif
