#include <ncurses.h>
#include <malloc.h>
#include "stack.h"
#include "deck.h"
#include "display.h"
#include "game.h"
#include "cursor.h"

void allocate_cursor(struct cursor **cursor) {
  *cursor = malloc(sizeof(**cursor));

  return;
}

void initialize_cursor(struct cursor *cursor) {
  cursor->x = CURSOR_STARTING_X;
  cursor->y = CURSOR_STARTING_Y;

  return;
}

void draw_cursor(struct cursor *cursor) {
  mvaddch(cursor->y, cursor->x, '*');

  return;
}

void erase_cursor(struct cursor *cursor) {
  mvdelch(cursor->y, cursor->x);

  return;
}

void move_cursor(struct cursor *cursor, enum movement movement) {
  switch (movement) {
    case LEFT:
      if (cursor->x > CURSOR_STARTING_X) {
        erase_cursor(cursor);
        cursor->x = cursor->x - 8;
        if (cursor->y > CURSOR_STARTING_Y) {
          move_cursor(cursor, UP);
          move_cursor(cursor, DOWN);
        }
        draw_cursor(cursor);
      }
      break;
    case DOWN:
      if (cursor->y == CURSOR_STARTING_Y) {
        erase_cursor(cursor);
        switch (cursor->x - 3) {
          case MANEUVRE_0_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_0);
            break;
          case MANEUVRE_1_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_1);
            break;
          case MANEUVRE_2_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_2);
            break;
          case MANEUVRE_3_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_3);
            break;
          case MANEUVRE_4_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_4);
            break;
          case MANEUVRE_5_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_5);
            break;
          case MANEUVRE_6_STARTING_X:
            cursor->y = cursor->y + 7 + length(deck->maneuvre_6);
            break;
        }
        draw_cursor(cursor);
      }
      break;
    case RIGHT:
      if (cursor->x < 49) {
        erase_cursor(cursor);
        cursor->x = cursor->x + 8;
        if (cursor->y > CURSOR_STARTING_Y) {
          move_cursor(cursor, UP);
          move_cursor(cursor, DOWN);
        }
        draw_cursor(cursor);
      }
      break;
    case UP:
      if (cursor->y > 1) {
        erase_cursor(cursor);
        cursor->y = CURSOR_STARTING_Y;
        draw_cursor(cursor);
      }
      break;
  }

  /* this is needed because of the screen glitch that moving the cursor
   * on the maneuvre's stacks causes */
  refresh();
  draw_game(deck);

  return;
}

bool cursor_on_stock(struct cursor *cursor) {
  return((cursor->x == CURSOR_STARTING_X) && (cursor->y == CURSOR_STARTING_Y));
}
