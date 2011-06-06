#include <assert.h>
#include "test_helper.h"
#include "../src/card.h"

void test_card_init() {
  struct card *card;

  card_malloc(&card);
  card_init(card);

  assert(card->value == NO_VALUE);
  assert(card->suit == NO_SUIT);
  assert(card->face == NO_FACE);

  card_free(card);
}

void test_card_dup() {
  struct card *card_0, *card_1;
  const int begin_y = 5, begin_x = 10;

  card_malloc(&card_0);
  card_set(card_0, ACE, SPADES, EXPOSED, begin_y, begin_x);
  card_1 = card_dup(card_0);

  assert(card_0 != card_1);
  assert(cards_equal(card_0, card_1));
}

void test_card_set() {
  struct card *card;
  int begin_y = 5;
  int begin_x = 10;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, begin_y, begin_x);

  assert(card->value == ACE);
  assert(card->suit == SPADES);
  assert(card->face == EXPOSED);
  assert(card->frame->begin_y == begin_y);
  assert(card->frame->begin_x == begin_x);

  card_free(card);
}

void test_card_expose() {
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_expose(card);

  assert(card->face == EXPOSED);

  card_free(card);
}

void test_card_cover() {
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_cover(card);

  assert(card->face == COVERED);

  card_free(card);
}

void test_card() {
  test_card_init();
  test_card_dup();
  test_card_set();
  test_card_expose();
  test_card_cover();
}
