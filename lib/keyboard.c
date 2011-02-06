#include "display.h"
#include "keyboard.h"

void mark_origin(struct cursor *cursor) {
  return;
}

struct stack *cursor_stack(struct cursor *cursor) {
  struct stack *cursor_stack = NULL;

  if (cursor->y == CURSOR_STARTING_Y) {
    switch (cursor->x) {
      case CURSOR_STOCK_X:        cursor_stack = deck->stock;        break;
      case CURSOR_WASTE_PILE_X:   cursor_stack = deck->waste_pile;   break;
      case CURSOR_FOUNDATION_0_X: cursor_stack = deck->foundation_0; break;
      case CURSOR_FOUNDATION_1_X: cursor_stack = deck->foundation_1; break;
      case CURSOR_FOUNDATION_2_X: cursor_stack = deck->foundation_2; break;
      case CURSOR_FOUNDATION_3_X: cursor_stack = deck->foundation_3; break;
    }
  } else {
    switch (cursor->x) {
      case CURSOR_MANEUVRE_0_X: cursor_stack = deck->maneuvre_0; break;
      case CURSOR_MANEUVRE_1_X: cursor_stack = deck->maneuvre_1; break;
      case CURSOR_MANEUVRE_2_X: cursor_stack = deck->maneuvre_2; break;
      case CURSOR_MANEUVRE_3_X: cursor_stack = deck->maneuvre_3; break;
      case CURSOR_MANEUVRE_4_X: cursor_stack = deck->maneuvre_4; break;
      case CURSOR_MANEUVRE_5_X: cursor_stack = deck->maneuvre_5; break;
      case CURSOR_MANEUVRE_6_X: cursor_stack = deck->maneuvre_6; break;
    }
  }

  return(cursor_stack);
}

bool cursor_on_stack(struct cursor *cursor, struct stack *stack) {
  return(cursor_stack(cursor) == stack);
}

bool cursor_on_invalid_spot(struct cursor *cursor) {
  return(cursor->x == CURSOR_INVALID_SPOT_X &&
         cursor->y == CURSOR_INVALID_SPOT_Y);
}
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

void handle_card_movement(struct cursor *cursor) {
  struct stack *origin = NULL;
  struct stack *destination = NULL;
  int option;

  mark_origin(cursor);
  origin = cursor_stack(cursor);

  /* trying to move cards from the space between the waste pile and the
   * foundations */
  if (cursor_on_invalid_spot(cursor)) {
    return;
  }

  while (1) {
    switch (option = getch()) {
      case 'h':
      case KEY_LEFT:
        move_cursor(cursor, LEFT);
        break;
      case 'j':
      case KEY_DOWN:
        move_cursor(cursor, DOWN);
        break;
      case 'k':
      case KEY_UP:
        move_cursor(cursor, UP);
        break;
      case 'l':
      case KEY_RIGHT:
        move_cursor(cursor, RIGHT);
        break;
      case KEY_SPACEBAR:
        if (!cursor_on_invalid_spot(cursor) &&
            !cursor_on_stock(cursor) &&
            !cursor_on_stack(cursor, origin)) {
          destination = cursor_stack(cursor);
          move_card(&origin, &destination);
          draw_stack(origin);
          draw_stack(destination);
        }
        return;
    }
  }

  return;
}

void handle_keyboard_event(int key) {
  switch (key) {
  case 'h':
  case KEY_LEFT:
    move_cursor(cursor, LEFT);
    break;
  case 'j':
  case KEY_DOWN:
    move_cursor(cursor, DOWN);
    break;
  case 'k':
  case KEY_UP:
    move_cursor(cursor, UP);
    break;
  case 'l':
  case KEY_RIGHT:
    move_cursor(cursor, RIGHT);
    break;
  case KEY_SPACEBAR:
    if (cursor_on_stock(cursor)) {
      handle_stock_event();
    } else {
      handle_card_movement(cursor);
    }
    break;
  }

  return;
}
