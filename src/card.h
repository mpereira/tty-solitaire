#ifndef CARD_H
#define CARD_H

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

void allocate_card(struct card **);
void initialize_card(struct card *);
struct card *duplicate_card(struct card *);
void free_card(struct card *);
void set_card(struct card *, enum value, enum suit, enum face, int, int);
void expose_card(struct card *);
void cover_card(struct card *);

#endif
