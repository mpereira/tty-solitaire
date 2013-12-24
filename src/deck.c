#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "deck.h"
#include "common.h"

void deck_malloc(struct deck **deck) {
  if (!(*deck = malloc(sizeof(**deck)))) {
    tty_solitaire_generic_error(errno, __FILE__, __LINE__);
  }
  stack_malloc(&((*deck)->stock));
  stack_malloc(&((*deck)->waste_pile));
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    stack_malloc(&((*deck)->foundation[i]));
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    stack_malloc(&((*deck)->maneuvre[i]));
  }
}

void deck_init(struct deck *deck) {
  stack_init(deck->stock);
  stack_init(deck->waste_pile);
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    stack_init(deck->foundation[i]);
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    stack_init(deck->maneuvre[i]);
  }
}

void deck_free(struct deck *deck) {
  stack_free(deck->stock);
  stack_free(deck->waste_pile);
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    stack_free(deck->foundation[i]);
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    stack_free(deck->maneuvre[i]);
  }
  free(deck);
}
