#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <ncurses.h>

#include "cursor.h"
#include "game.h"
#include "common.h"

void allocate_cursor(struct cursor **cursor) {
  if (!(*cursor = malloc(sizeof(**cursor)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }
  (*cursor)->window = newwin(1, 1, CURSOR_BEGIN_Y, CURSOR_BEGIN_X);
}

void initialize_cursor(struct cursor *cursor) {
  mvwin(cursor->window, CURSOR_BEGIN_Y, CURSOR_BEGIN_X);
  cursor->y = CURSOR_BEGIN_Y;
  cursor->x = CURSOR_BEGIN_X;
  cursor->marked = false;
}

void free_cursor(struct cursor *cursor) {
  delwin(cursor->window);
  free(cursor);
}

void mark_cursor(struct cursor *cursor) {
  cursor->marked = true;
}

void unmark_cursor(struct cursor *cursor) {
  cursor->marked = false;
}

void move_cursor(struct cursor *cursor, enum movement movement) {
  switch (movement) {
  case LEFT:
    if (cursor->x > CURSOR_BEGIN_X) {
      cursor->x = cursor->x - 8;
      if (cursor->y > CURSOR_BEGIN_Y) {
        move_cursor(cursor, UP);
        move_cursor(cursor, DOWN);
      }
    }
    break;
  case DOWN:
    if (cursor->y == CURSOR_BEGIN_Y) {
      switch (cursor->x - 3) {
      case MANEUVRE_0_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[0]);
        break;
      case MANEUVRE_1_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[1]);
        break;
      case MANEUVRE_2_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[2]);
        break;
      case MANEUVRE_3_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[3]);
        break;
      case MANEUVRE_4_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[4]);
        break;
      case MANEUVRE_5_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[5]);
        break;
      case MANEUVRE_6_BEGIN_X:
        cursor->y = cursor->y + 7 + length(deck->maneuvre[6]);
        break;
      }
    }
    break;
  case RIGHT:
    if (cursor->x < 49) {
      cursor->x = cursor->x + 8;
      if (cursor->y > CURSOR_BEGIN_Y) {
        move_cursor(cursor, UP);
        move_cursor(cursor, DOWN);
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
