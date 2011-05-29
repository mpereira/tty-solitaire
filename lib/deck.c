#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "deck.h"
#include "common.h"

void allocate_deck(struct deck **deck) {
  if (!(*deck = malloc(sizeof(**deck)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }

  allocate_stack(&((*deck)->stock));
  allocate_stack(&((*deck)->waste_pile));
  for (int i = 0; i < 4; i++) {
    allocate_stack(&((*deck)->foundation[i]));
  }
  for (int i = 0; i < 7; i++) {
    allocate_stack(&((*deck)->maneuvre[i]));
  }
}

void initialize_deck(struct deck *deck) {
  initialize_stack(deck->stock);
  initialize_stack(deck->waste_pile);
  for (int i = 0; i < 4; i++) {
    initialize_stack(deck->foundation[i]);
  }
  for (int i = 0; i < 7; i++) {
    initialize_stack(deck->maneuvre[i]);
  }
}

void free_deck(struct deck *deck) {
  if (deck) {
    free_stack(deck->stock);
    free_stack(deck->waste_pile);
    for (int i = 0; i < 4; i++) {
      free_stack(deck->foundation[i]);
    }
    for (int i = 0; i < 7; i++) {
      free_stack(deck->maneuvre[i]);
    }
  }
  free(deck);
}
