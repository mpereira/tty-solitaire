#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>
#include "display.h"
#include "game.h"
#include "cursor.h"

void allocate_cursor(struct cursor **cursor) {
  if (!(*cursor = malloc(sizeof(**cursor)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }
}

void initialize_cursor(struct cursor *cursor) {
  cursor->x = CURSOR_STARTING_X;
  cursor->y = CURSOR_STARTING_Y;
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
  draw_deck(deck);
}
