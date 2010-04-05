#include <ncurses.h>
#include <malloc.h>
#include "card.h"

void allocate_card(struct card **card) {
  *card = malloc(sizeof(**card));

  allocate_frame(&((*card)->frame));

  return;
}

void initialize_card(struct card *card) {
  initialize_frame(card->frame);
  card->value   = NO_VALUE;
  card->suit    = NO_SUIT;
  card->face    = NO_FACE;

  return;
}

void delete_card(struct card *card) {
  delete_frame(card->frame);
  free(card);

  return;
}

void set_card(struct card *card,
              enum value value,
              enum suit suit,
              enum face face,
              int start_y,
              int start_x) {
  set_frame(card->frame, start_y, start_x);
  card->value = value;
  card->suit = suit;
  card->face = face;

  return;
}
