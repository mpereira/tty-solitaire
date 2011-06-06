#ifndef TTY_SOLITAIRE_TEST_HELPER_H
#define TTY_SOLITAIRE_TEST_HELPER_H

#include <stdbool.h>
#include "../src/frame.h"
#include "../src/card.h"
#include "../src/stack.h"

bool frames_equal(struct frame *, struct frame *);
bool cards_equal(struct card *, struct card *);
bool stacks_equal(struct stack *, struct stack *);

#endif
