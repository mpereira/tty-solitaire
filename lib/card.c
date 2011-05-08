#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "card.h"
#include "common.h"

void allocate_card(struct card **card) {
  if (!(*card = malloc(sizeof(**card)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }

  allocate_frame(&((*card)->frame));
}

void initialize_card(struct card *card) {
  initialize_frame(card->frame);
  card->value = NO_VALUE;
  card->suit = NO_SUIT;
  card->face = NO_FACE;
}

struct card *duplicate_card(struct card *card) {
  struct card *new_card;

  allocate_card(&new_card);
  set_card(new_card,
           card->value,
           card->suit,
           card->face,
           card->frame->start_y,
           card->frame->start_x);

  return(new_card);
}

void free_card(struct card *card) {
  if (card) {
    free_frame(card->frame);
  }
  free(card);
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
}

void expose_card(struct card *card) {
  card->face = EXPOSED;
}

void cover_card(struct card *card) {
  card->face = COVERED;
}
