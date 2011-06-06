#ifndef TTY_SOLITAIRE_CARD_H
#define TTY_SOLITAIRE_CARD_H

#include "frame.h"

enum value {
  NO_VALUE = -1,
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
};
enum suit { NO_SUIT = -1, DIAMONDS, SPADES, HEARTS, CLUBS };
enum face { NO_FACE = -1, COVERED, EXPOSED };

struct card {
  struct frame *frame;
  enum value   value;
  enum suit    suit;
  enum face    face;
};

void card_malloc(struct card **);
void card_init(struct card *);
void card_free(struct card *);
void card_set(struct card *, enum value, enum suit, enum face, int, int);
void card_expose(struct card *);
void card_cover(struct card *);
void card_mark(struct card *);
void card_unmark(struct card *);
struct card *card_dup(struct card *);

#endif
