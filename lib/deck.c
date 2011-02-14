#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "deck.h"

void allocate_deck(struct deck **deck) {
  if (!(*deck = malloc(sizeof(**deck)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }

  allocate_stack(&((*deck)->stock));
  allocate_stack(&((*deck)->waste_pile));

  allocate_stack(&((*deck)->foundation_0));
  allocate_stack(&((*deck)->foundation_1));
  allocate_stack(&((*deck)->foundation_2));
  allocate_stack(&((*deck)->foundation_3));

  allocate_stack(&((*deck)->maneuvre_0));
  allocate_stack(&((*deck)->maneuvre_1));
  allocate_stack(&((*deck)->maneuvre_2));
  allocate_stack(&((*deck)->maneuvre_3));
  allocate_stack(&((*deck)->maneuvre_4));
  allocate_stack(&((*deck)->maneuvre_5));
  allocate_stack(&((*deck)->maneuvre_6));

  return;
}

void initialize_deck(struct deck *deck) {
  initialize_stack(deck->stock);
  initialize_stack(deck->waste_pile);

  initialize_stack(deck->foundation_0);
  initialize_stack(deck->foundation_1);
  initialize_stack(deck->foundation_2);
  initialize_stack(deck->foundation_3);

  initialize_stack(deck->maneuvre_0);
  initialize_stack(deck->maneuvre_1);
  initialize_stack(deck->maneuvre_2);
  initialize_stack(deck->maneuvre_3);
  initialize_stack(deck->maneuvre_4);
  initialize_stack(deck->maneuvre_5);
  initialize_stack(deck->maneuvre_6);

  return;
}

void free_deck(struct deck *deck) {
  if (deck) {
    free_stack(deck->waste_pile);

    free_stack(deck->foundation_0);
    free_stack(deck->foundation_1);
    free_stack(deck->foundation_2);
    free_stack(deck->foundation_3);

    free_stack(deck->maneuvre_0);
    free_stack(deck->maneuvre_1);
    free_stack(deck->maneuvre_2);
    free_stack(deck->maneuvre_3);
    free_stack(deck->maneuvre_4);
    free_stack(deck->maneuvre_5);
    free_stack(deck->maneuvre_6);
  }
  free(deck);

  return;
}
