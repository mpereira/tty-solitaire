#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include "card.h"
#include "display.h"

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
