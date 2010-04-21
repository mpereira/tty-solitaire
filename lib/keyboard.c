#include <stdio.h>
#include "display.h"
#include "keyboard.h"

void handle_stock_event() {
  if (!empty(deck->stock)) {
    /* erase the stack before emptying it */
    if (length(deck->stock) == 1) {
      erase_stack(deck->stock);
    }
    move_card(&(deck->stock), &(deck->waste_pile));
    expose_card(deck->waste_pile->card);
    draw_stack(deck->stock);
    draw_stack(deck->waste_pile);
  }

  return;
}

int key_event() {
  int pressed_key;

  pressed_key = getchar();

  return(pressed_key);
}
