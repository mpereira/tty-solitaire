#ifndef DISPLAY_H
#define DISPLAY_H

#define DIAMONDS_SYMBOL "\u2666"
#define SPADES_SYMBOL   "\u2660"
#define HEARTS_SYMBOL   "\u2665"
#define CLUBS_SYMBOL    "\u2663"

void init_curses();
char *card_suit(enum suit);

#endif
