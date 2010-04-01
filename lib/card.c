#include <ncurses.h>
#include <malloc.h>
#include "card.h"
#include "frame.h"
#include "../src/common.h"

struct card *initialize_card() {
  struct card *card = NULL;

  card = malloc(sizeof(card));

  card->frame   = initialize_frame();
  card->value   = NONE;
  card->suit    = NONE;
  card->exposed = FALSE;

  return(card);
}

void delete_card(struct card *card) {
  delete_frame(card->frame);
  free(card);

  return;
}

void set_card(struct card *card,
              enum value value,
              enum suit suit,
              char exposed,
              int start_y,
              int start_x) {
  set_frame(card->frame, start_y, start_x);
  card->value = value;
  card->suit = suit;
  card->exposed = exposed;

  return;
}

void refresh_card(struct card *card) {
  box(card->frame->shape, 0, 0);
  wrefresh(card->frame->shape);
}
