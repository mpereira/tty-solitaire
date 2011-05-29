#include <stdlib.h>
#include <assert.h>

#include "card.h"
#include "game.h"
#include "display.h"
#include "curses.h"
#include "keyboard.h"

static bool cursor_on_stock(struct cursor *cursor) {
  return((cursor->x == CURSOR_BEGIN_X) && (cursor->y == CURSOR_BEGIN_Y));
}

static struct stack *cursor_stack(struct cursor *cursor) {
  if (cursor->y == CURSOR_BEGIN_Y) {
    switch (cursor->x) {
    case CURSOR_STOCK_X:        return(deck->stock);
    case CURSOR_WASTE_PILE_X:   return(deck->waste_pile);
    case CURSOR_FOUNDATION_0_X: return(deck->foundation[0]);
    case CURSOR_FOUNDATION_1_X: return(deck->foundation[1]);
    case CURSOR_FOUNDATION_2_X: return(deck->foundation[2]);
    case CURSOR_FOUNDATION_3_X: return(deck->foundation[3]);
    default: assert(false && "invalid stack");
    }
  } else {
    switch (cursor->x) {
    case CURSOR_MANEUVRE_0_X: return(deck->maneuvre[0]);
    case CURSOR_MANEUVRE_1_X: return(deck->maneuvre[1]);
    case CURSOR_MANEUVRE_2_X: return(deck->maneuvre[2]);
    case CURSOR_MANEUVRE_3_X: return(deck->maneuvre[3]);
    case CURSOR_MANEUVRE_4_X: return(deck->maneuvre[4]);
    case CURSOR_MANEUVRE_5_X: return(deck->maneuvre[5]);
    case CURSOR_MANEUVRE_6_X: return(deck->maneuvre[6]);
    default: assert(false && "invalid stack");
    }
  }
}

static bool cursor_on_invalid_spot(struct cursor *cursor) {
  return(cursor->x == CURSOR_INVALID_SPOT_X &&
           cursor->y == CURSOR_INVALID_SPOT_Y);
}

static void handle_stock_event() {
  if (!empty(deck->stock)) {
    move_card(&(deck->stock), &(deck->waste_pile));
    expose_card(deck->waste_pile->card);
    draw_stack(deck->stock);
    draw_stack(deck->waste_pile);
  }
}

static void handle_card_movement(struct cursor *cursor) {
  struct stack *origin = NULL;
  struct stack *destination = NULL;
  int option;

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
      draw_cursor(cursor);
      break;
    case 'j':
    case KEY_DOWN:
      move_cursor(cursor, DOWN);
      draw_cursor(cursor);
      break;
    case 'k':
    case KEY_UP:
      move_cursor(cursor, UP);
      draw_cursor(cursor);
      break;
    case 'l':
    case KEY_RIGHT:
      move_cursor(cursor, RIGHT);
      draw_cursor(cursor);
      break;
    case KEY_SPACEBAR:
      destination = cursor_stack(cursor);
      if (valid_move(origin, destination)) {
        move_card(&origin, &destination);
        draw_stack(origin);
        draw_stack(destination);
      }
      return;
    case 'q':
    case 'Q':
      end_curses();
      end_game();
      exit(0);
    }
  }
}

void handle_keyboard_event(int key) {
  switch (key) {
  case 'h':
  case KEY_LEFT:
    move_cursor(cursor, LEFT);
    draw_cursor(cursor);
    break;
  case 'j':
  case KEY_DOWN:
    move_cursor(cursor, DOWN);
    draw_cursor(cursor);
    break;
  case 'k':
  case KEY_UP:
    move_cursor(cursor, UP);
    draw_cursor(cursor);
    break;
  case 'l':
  case KEY_RIGHT:
    move_cursor(cursor, RIGHT);
    draw_cursor(cursor);
    break;
  case KEY_SPACEBAR:
    if (cursor_on_stock(cursor)) {
      handle_stock_event();
    } else {
      handle_card_movement(cursor);
    }
    break;
  }
}
