#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include "frame.h"
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

char *card_value(enum value value) {
  char *card_value;

  card_value = malloc(2 * sizeof(card_value));

  switch(value) {
    case TWO:   card_value = "2";  break;
    case THREE: card_value = "3";  break;
    case FOUR:  card_value = "4";  break;
    case FIVE:  card_value = "5";  break;
    case SIX:   card_value = "6";  break;
    case SEVEN: card_value = "7";  break;
    case EIGHT: card_value = "8";  break;
    case NINE:  card_value = "9";  break;
    case TEN:   card_value = "10"; break;
    case JACK:  card_value = "J";  break;
    case QUEEN: card_value = "Q";  break;
    case KING:  card_value = "K";  break;
    case ACE:   card_value = "A";  break;
    default:    card_value = "?";
  }

  return(card_value);
}
