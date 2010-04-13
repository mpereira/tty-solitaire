#include <malloc.h>
#include "deck.h"

void allocate_deck(struct deck **deck) {
  *deck = malloc(sizeof(**deck));

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

void delete_deck(struct deck *deck) {
  delete_stack(deck->stock);
  delete_stack(deck->waste_pile);

  delete_stack(deck->foundation_0);
  delete_stack(deck->foundation_1);
  delete_stack(deck->foundation_2);
  delete_stack(deck->foundation_3);

  delete_stack(deck->maneuvre_0);
  delete_stack(deck->maneuvre_1);
  delete_stack(deck->maneuvre_2);
  delete_stack(deck->maneuvre_3);
  delete_stack(deck->maneuvre_4);
  delete_stack(deck->maneuvre_5);
  delete_stack(deck->maneuvre_6);

  free(deck);

  return;
}
