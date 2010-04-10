#include <stdio.h>
#include "stack_debug.h"
#include "deck_debug.h"

void print_deck(struct deck *deck) {
  puts("stock");
  print_stack(deck->stock);
  puts("");
  puts("waste_pile");
  print_stack(deck->waste_pile);
  puts("");

  puts("foundation_0");
  print_stack(deck->foundation_0);
  puts("");
  puts("foundation_1");
  print_stack(deck->foundation_1);
  puts("");
  puts("foundation_2");
  print_stack(deck->foundation_2);
  puts("");
  puts("foundation_3");
  print_stack(deck->foundation_3);
  puts("");

  puts("maneuvre_0");
  print_stack(deck->maneuvre_0);
  puts("");
  puts("maneuvre_1");
  print_stack(deck->maneuvre_1);
  puts("");
  puts("maneuvre_2");
  print_stack(deck->maneuvre_2);
  puts("");
  puts("maneuvre_3");
  print_stack(deck->maneuvre_3);
  puts("");
  puts("maneuvre_4");
  print_stack(deck->maneuvre_4);
  puts("");
  puts("maneuvre_5");
  print_stack(deck->maneuvre_5);
  puts("");
  puts("maneuvre_6");
  print_stack(deck->maneuvre_6);
  puts("");

  return;
}
