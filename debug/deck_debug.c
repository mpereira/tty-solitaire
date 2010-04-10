#include <stdio.h>
#include "deck_debug.h"

void print_deck(struct deck *deck) {
  print_stack(deck->stock);
  print_stack(deck->waste_pile);

  print_stack(deck->foundation_0);
  print_stack(deck->foundation_1);
  print_stack(deck->foundation_2);
  print_stack(deck->foundation_3);

  print_stack(deck->maneuvre_0);
  print_stack(deck->maneuvre_1);
  print_stack(deck->maneuvre_2);
  print_stack(deck->maneuvre_3);
  print_stack(deck->maneuvre_4);
  print_stack(deck->maneuvre_5);
  print_stack(deck->maneuvre_6);

  return;
}
