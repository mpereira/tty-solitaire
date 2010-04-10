#include <stdio.h>
#include "card_debug.h"

void print_card(struct card *card) {
  switch (card->face) {
    case NO_FACE: printf("No face "); break;
    case COVERED: printf("Covered "); break;
    case EXPOSED: printf("Exposed "); break;
    default     : printf("?");
  }

  switch (card->value) {
    case NO_VALUE: printf(", no value "); break;
    case TWO     : printf("two"); break;
    case THREE   : printf("three "); break;
    case FOUR    : printf("four "); break;
    case FIVE    : printf("five"); break;
    case SIX     : printf("six"); break;
    case SEVEN   : printf("seven"); break;
    case EIGHT   : printf("eight"); break;
    case NINE    : printf("nine"); break;
    case TEN     : printf("ten"); break;
    case JACK    : printf("jack"); break;
    case QUEEN   : printf("queen "); break;
    case KING    : printf("king "); break;
    case ACE     : printf("ace "); break;
    default      : printf("?");
  }

  switch (card->suit) {
    case NO_SUIT : printf(", no suit "); break;
    case DIAMONDS: printf("of diamonds "); break;
    case SPADES  : printf("of spades "); break;
    case HEARTS  : printf("of hearts "); break;
    case CLUBS   : printf("of clubs "); break;
  }

  printf("at y:%d x:%d, ", card->frame->start_y, card->frame->start_x);
  printf("with width:%d height:%d\n", FRAME_WIDTH, FRAME_HEIGHT);

  return;
}
