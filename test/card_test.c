#include <assert.h>
#include "../lib/card.h"

void test_initialize_card() {
  struct card *card;

  allocate_card(&card);
  initialize_card(card);

  assert(card->value == NO_VALUE);
  assert(card->suit == NO_SUIT);
  assert(card->face == NO_FACE);

  delete_card(card);

  return;
}

void test_set_card() {
  struct card *card;
  int start_y = 5;
  int start_x = 10;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, start_y, start_x);

  assert(card->value == ACE);
  assert(card->suit == SPADES);
  assert(card->face == EXPOSED);
  assert(card->frame->start_y == start_y);
  assert(card->frame->start_x == start_x);

  delete_card(card);

  return;
}

void test_expose_card() {
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  expose_card(card);

  assert(card->face == EXPOSED);

  delete_card(card);

  return;
}

void test_cover_card() {
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  cover_card(card);

  assert(card->face == COVERED);

  delete_card(card);

  return;
}

void test_card() {
  test_initialize_card();
  test_set_card();
  test_expose_card();
  test_cover_card();

  return;
}
