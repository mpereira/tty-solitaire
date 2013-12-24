#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "card.h"
#include "common.h"

void card_malloc(struct card **card) {
  if (!(*card = malloc(sizeof(**card)))) {
    tty_solitaire_generic_error(errno, __FILE__, __LINE__);
  }
  frame_malloc(&((*card)->frame));
}

void card_init(struct card *card) {
  frame_init(card->frame);
  card->value = NO_VALUE;
  card->suit = NO_SUIT;
  card->face = NO_FACE;
}

void card_free(struct card *card) {
  frame_free(card->frame);
  free(card);
}

void card_set(struct card *card,
              enum value value,
              enum suit suit,
              enum face face,
              int begin_y,
              int begin_x) {
  frame_set(card->frame, begin_y, begin_x);
  card->value = value;
  card->suit = suit;
  card->face = face;
}

void card_expose(struct card *card) {
  card->face = EXPOSED;
}

void card_cover(struct card *card) {
  card->face = COVERED;
}

void card_mark(struct card *card) {
  frame_set(card->frame, card->frame->begin_y + 1, card->frame->begin_x);
}

void card_unmark(struct card *card) {
  frame_set(card->frame, card->frame->begin_y - 1, card->frame->begin_x);
}

struct card *card_dup(struct card *card) {
  struct card *new_card;

  card_malloc(&new_card);
  card_set(new_card,
           card->value,
           card->suit,
           card->face,
           card->frame->begin_y,
           card->frame->begin_x);

  return(new_card);
}
