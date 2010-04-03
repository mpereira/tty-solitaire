#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include "card.h"
#include "display.h"

void init_curses() {
  setlocale(LC_ALL, "");    /* supporting unicode characters          */
  initscr();                /* initialize the terminal in curses mode */
  raw();                    /* disable line buffers                   */
  noecho();                 /* character echo is unnecessary          */
  keypad(stdscr, TRUE);     /* enable F and arrow keys                */
}

char *card_suit(enum suit suit) {
  char *card_suit;

  card_suit = malloc(5 * sizeof(card_suit));

  switch(suit) {
    case DIAMONDS: strcpy(card_suit, DIAMONDS_SYMBOL); break;
    case SPADES:   strcpy(card_suit, SPADES_SYMBOL);   break;
    case HEARTS:   strcpy(card_suit, HEARTS_SYMBOL);   break;
    case CLUBS:    strcpy(card_suit, CLUBS_SYMBOL);    break;
    default:       strcpy(card_suit, "?");
  }

  return(card_suit);
}
