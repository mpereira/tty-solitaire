#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

#include "deck.h"
#include "common.h"

void allocate_deck(struct deck **deck) {
  if (!(*deck = malloc(sizeof(**deck)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
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

void initialize_deck(struct deck *deck) {
  stack_init(deck->stock);
  stack_init(deck->waste_pile);
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    stack_init(deck->foundation[i]);
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    stack_init(deck->maneuvre[i]);
  }
}

void free_deck(struct deck *deck) {
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
