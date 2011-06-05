#include <stdlib.h>
#include <assert.h>

#include "keyboard.h"
#include "card.h"
#include "stack.h"
#include "game.h"
#include "cursor.h"
#include "draw.h"

static struct stack **cursor_stack(struct cursor *cursor) {
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

static bool cursor_on_stock(struct cursor *cursor) {
  return(cursor_stack(cursor) && *cursor_stack(cursor) == deck->stock);
}

static bool cursor_on_invalid_spot(struct cursor *cursor) {
  return(!cursor_stack(cursor));
}

static void handle_stock_event() {
  if (!empty(deck->stock)) {
    move_card(&(deck->stock), &(deck->waste_pile));
    expose_card(deck->waste_pile->card);
    erase_stack(deck->waste_pile);
    draw_stack(deck->stock);
    draw_stack(deck->waste_pile);
  }
}

static int marked_cards_count(struct stack *stack) {
  if (length(stack) == 1) {
    if (stack->card->frame->begin_y > MANEUVRE_BEGIN_Y) {
      return(1);
    }
  } else if (length(stack) > 1) {
    for (int marked_cards_count = 0; stack; stack = stack->next) {
      marked_cards_count++;
      if (!stack->next || (stack->card->frame->begin_y -
                             stack->next->card->frame->begin_y) > 1) {
        return(marked_cards_count);
      }
    }
  }
  return(0);
}

static void unmark_cards(struct stack *stack) {
  int marked_cards = marked_cards_count(stack);
  for (int i = 0; i < marked_cards; stack = stack->next, i++) {
    unmark_card(stack->card);
  }
}

static void handle_card_movement(struct cursor *cursor) {
  struct stack **origin = cursor_stack(cursor);
  struct stack **destination;
  int option;

  if (cursor_on_invalid_spot(cursor) || empty(*origin)) {
    return;
  }

  if (maneuvre_stack(*origin)) {
    erase_stack(*origin);
    mark_card((*origin)->card);
    draw_stack(*origin);
    cursor->y++;
  }
  erase_cursor(cursor);
  mark_cursor(cursor);
  draw_cursor(cursor);

  while (1) {
    switch (option = getch()) {
    case 'h':
    case KEY_LEFT:
      erase_cursor(cursor);
      move_cursor(cursor, LEFT);
      draw_cursor(cursor);
      break;
    case 'j':
    case KEY_DOWN:
      erase_cursor(cursor);
      move_cursor(cursor, DOWN);
      draw_cursor(cursor);
      break;
    case 'k':
    case KEY_UP:
      erase_cursor(cursor);
      move_cursor(cursor, UP);
      draw_cursor(cursor);
      break;
    case 'l':
    case KEY_RIGHT:
      erase_cursor(cursor);
      move_cursor(cursor, RIGHT);
      draw_cursor(cursor);
      break;
    case 'm':
      if (origin == cursor_stack(cursor) && maneuvre_stack(*origin)) {
        for (struct stack *i = *origin; i && i->next; i = i->next) {
          if (i->next->card->face == EXPOSED &&
                (i->card->frame->begin_y - i->next->card->frame->begin_y) > 1) {
            erase_stack(*origin);
            mark_card(i->next->card);
            draw_stack(*origin);
            break;
          }
        }
      }
      break;
    case 'n':
      if (origin == cursor_stack(cursor) && maneuvre_stack(*origin)) {
        for (struct stack *i = (*origin)->next; i; i = i->next) {
          if (i->next) {
            if ((i->card->frame->begin_y - i->next->card->frame->begin_y) > 1) {
              erase_stack(*origin);
              unmark_card(i->card);
              draw_stack(*origin);
              break;
            }
          } else {
            if (i->card->frame->begin_y == (MANEUVRE_BEGIN_Y + 1)) {
              erase_stack(*origin);
              unmark_card(i->card);
              draw_stack(*origin);
              break;
            }
          }
        }
      }
      break;
    case KEY_SPACEBAR:
      destination = cursor_stack(cursor);
      if (maneuvre_stack(*origin) && marked_cards_count(*origin) > 0) {
        erase_stack(*origin);
        unmark_cards(*origin);
        draw_stack(*origin);
      }
      /* As 'destination' can be NULL if the cursor is at the invalid spot we
       * check it before dereferencing */
      if (destination && valid_move(*origin, *destination)) {
        erase_stack(*origin);
        move_card(origin, destination);
        draw_stack(*origin);
        draw_stack(*destination);
        if (maneuvre_stack(*destination) && length(*destination) > 1) {
          erase_cursor(cursor);
          cursor->y++;
          draw_cursor(cursor);
        }
      }
      if (destination && *origin == *destination) {
        erase_cursor(cursor);
        cursor->y--;
      }
      unmark_cursor(cursor);
      draw_cursor(cursor);
      return;
    case KEY_ESCAPE:
      if (cursor_stack(cursor) == origin && maneuvre_stack(*origin)) {
        erase_cursor(cursor);
        cursor->y--;
      }
      if (marked_cards_count(*origin) > 0) {
        erase_stack(*origin);
        unmark_cards(*origin);
        draw_stack(*origin);
      }
      if (cursor->marked) {
        unmark_cursor(cursor);
        draw_cursor(cursor);
      }
      return;
    case 'q':
    case 'Q':
      endwin();
      game_end();
      exit(0);
    }
  }
}

void handle_keyboard_event(int key) {
  switch (key) {
  case 'h':
  case KEY_LEFT:
    erase_cursor(cursor);
    move_cursor(cursor, LEFT);
    draw_cursor(cursor);
    break;
  case 'j':
  case KEY_DOWN:
    erase_cursor(cursor);
    move_cursor(cursor, DOWN);
    draw_cursor(cursor);
    break;
  case 'k':
  case KEY_UP:
    erase_cursor(cursor);
    move_cursor(cursor, UP);
    draw_cursor(cursor);
    break;
  case 'l':
  case KEY_RIGHT:
    erase_cursor(cursor);
    move_cursor(cursor, RIGHT);
    draw_cursor(cursor);
    break;
  case KEY_SPACEBAR:
    if (cursor_on_stock(cursor)) {
      handle_stock_event();
    } else {
      struct card *card;
      if (cursor_stack(cursor) &&
            (card = (*cursor_stack(cursor))->card)->face == COVERED) {
        expose_card(card);
        draw_card(card);
      } else {
        handle_card_movement(cursor);
      }
    }
    break;
  }
}
