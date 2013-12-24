#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ncurses.h>
#include <assert.h>

#include "cursor.h"
#include "game.h"
#include "common.h"

void cursor_malloc(struct cursor **cursor) {
  if (!(*cursor = malloc(sizeof(**cursor)))) {
    tty_solitaire_generic_error(errno, __FILE__, __LINE__);
  }
  (*cursor)->window = newwin(1, 1, CURSOR_BEGIN_Y, CURSOR_BEGIN_X);
}

void cursor_init(struct cursor *cursor) {
  mvwin(cursor->window, CURSOR_BEGIN_Y, CURSOR_BEGIN_X);
  cursor->y = CURSOR_BEGIN_Y;
  cursor->x = CURSOR_BEGIN_X;
  cursor->marked = false;
}

void cursor_free(struct cursor *cursor) {
  delwin(cursor->window);
  free(cursor);
}

void cursor_mark(struct cursor *cursor) {
  cursor->marked = true;
}

void cursor_unmark(struct cursor *cursor) {
  cursor->marked = false;
}

void cursor_move(struct cursor *cursor, enum movement movement) {
  switch (movement) {
  case LEFT:
    if (cursor->x > CURSOR_BEGIN_X) {
      cursor->x = cursor->x - 8;
      if (cursor->y > CURSOR_BEGIN_Y) {
        cursor_move(cursor, UP);
        cursor_move(cursor, DOWN);
      }
    }
    break;
  case DOWN:
    if (cursor->y == CURSOR_BEGIN_Y) {
      switch (cursor->x - 3) {
      case MANEUVRE_0_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[0]);
        break;
      case MANEUVRE_1_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[1]);
        break;
      case MANEUVRE_2_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[2]);
        break;
      case MANEUVRE_3_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[3]);
        break;
      case MANEUVRE_4_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[4]);
        break;
      case MANEUVRE_5_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[5]);
        break;
      case MANEUVRE_6_BEGIN_X:
        cursor->y = cursor->y + 7 + stack_length(deck->maneuvre[6]);
        break;
      }
    }
    break;
  case RIGHT:
    if (cursor->x < 49) {
      cursor->x = cursor->x + 8;
      if (cursor->y > CURSOR_BEGIN_Y) {
        cursor_move(cursor, UP);
        cursor_move(cursor, DOWN);
      }
    }
    break;
  case UP:
    if (cursor->y > CURSOR_BEGIN_Y) {
      cursor->y = CURSOR_BEGIN_Y;
    }
    break;
  }
}

enum movement cursor_direction(int key) {
  switch (key) {
  case 'h':
  case KEY_LEFT:
    return(LEFT);
  case 'j':
  case KEY_DOWN:
    return(DOWN);
  case 'k':
  case KEY_UP:
    return(UP);
  case 'l':
  case KEY_RIGHT:
    return(RIGHT);
  default:
    endwin();
    game_end();
    assert(false && "invalid cursor direction");
  }
}

struct stack **cursor_stack(struct cursor *cursor) {
  if (cursor->y == CURSOR_BEGIN_Y) {
    switch (cursor->x) {
    case CURSOR_STOCK_X:        return(&(deck->stock));
    case CURSOR_WASTE_PILE_X:   return(&(deck->waste_pile));
    case CURSOR_FOUNDATION_0_X: return(&(deck->foundation[0]));
    case CURSOR_FOUNDATION_1_X: return(&(deck->foundation[1]));
    case CURSOR_FOUNDATION_2_X: return(&(deck->foundation[2]));
    case CURSOR_FOUNDATION_3_X: return(&(deck->foundation[3]));
    case CURSOR_INVALID_SPOT_X: return(NULL);
    default:
      endwin();
      game_end();
      assert(false && "invalid stack");
    }
  } else {
    switch (cursor->x) {
    case CURSOR_MANEUVRE_0_X: return(&(deck->maneuvre[0]));
    case CURSOR_MANEUVRE_1_X: return(&(deck->maneuvre[1]));
    case CURSOR_MANEUVRE_2_X: return(&(deck->maneuvre[2]));
    case CURSOR_MANEUVRE_3_X: return(&(deck->maneuvre[3]));
    case CURSOR_MANEUVRE_4_X: return(&(deck->maneuvre[4]));
    case CURSOR_MANEUVRE_5_X: return(&(deck->maneuvre[5]));
    case CURSOR_MANEUVRE_6_X: return(&(deck->maneuvre[6]));
    default:
      endwin();
      game_end();
      assert(false && "invalid stack");
    }
  }
}

bool cursor_on_stock(struct cursor *cursor) {
  return(cursor_stack(cursor) && *cursor_stack(cursor) == deck->stock);
}

bool cursor_on_invalid_spot(struct cursor *cursor) {
  return(!cursor_stack(cursor));
}
