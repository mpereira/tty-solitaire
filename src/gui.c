#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "gui.h"
#include "deck.h"
#include "game.h"

static const char *card_suits[4] = { "\u2666", "\u2660", "\u2665", "\u2663" };
static const char *card_values[13] = {
  "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
};

static void draw_value(struct card *card) {
  mvwprintw(card->frame->window, 0, 0, card_values[card->value]);
  mvwprintw(card->frame->window,
            4,
            7 - strlen(card_values[card->value]),
            card_values[card->value]);
}

static void draw_suit(struct card *card) {
  if (card->suit % 2 == 0) {
    wattron(card->frame->window, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattron(card->frame->window, COLOR_PAIR(BLACK_ON_WHITE));
  }
  mvwprintw(card->frame->window,
            0,
            strlen(card_values[card->value]),
            card_suits[card->suit]);
  mvwprintw(card->frame->window,
            4,
            6 - strlen(card_values[card->value]),
            card_suits[card->suit]);
  if (card->suit % 2 == 0) {
    wattroff(card->frame->window, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattroff(card->frame->window, COLOR_PAIR(BLACK_ON_WHITE));
  }
}

static void draw_front(struct card *card) {
  wbkgd(card->frame->window, COLOR_PAIR(BLACK_ON_WHITE));
  draw_value(card);
  draw_suit(card);
}

static void draw_back(struct card *card) {
  wbkgd(card->frame->window, COLOR_PAIR(WHITE_ON_BLUE));
  box(card->frame->window, 0, 0);
}

void draw_card(struct card *card) {
  if (card->face == EXPOSED) {
    draw_front(card);
  } else {
    draw_back(card);
  }
  wrefresh(card->frame->window);
}

void draw_stack(struct stack *stack) {
  if (stack_empty(stack)) {
    box(stack->card->frame->window, 0, 0);
    if (stock_stack(stack)) {
      if (game.passes_through_deck_left >= 1) {
        mvwprintw(stack->card->frame->window, 2, 3, "O");
      } else {
        mvwprintw(stack->card->frame->window, 2, 3, "X");
      }
    }
    wrefresh(stack->card->frame->window);
  } else {
    if (maneuvre_stack(stack)) {
      struct stack *stack_reversed_stack = stack_reverse(stack);
      for (struct stack *i = stack_reversed_stack; i; i = i->next) {
        draw_card(i->card);
      }
      stack_free(stack_reversed_stack);
    } else {
      draw_card(stack->card);
    }
  }
}

void draw_deck(struct deck *deck) {
  draw_stack(deck->stock);
  draw_stack(deck->waste_pile);
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    draw_stack(deck->foundation[i]);
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    draw_stack(deck->maneuvre[i]);
  }
}

void draw_cursor(struct cursor *cursor) {
  if (cursor->marked) {
    mvwin(cursor->window, cursor->y, cursor->x);
    waddch(cursor->window, '@');
  } else {
    mvwin(cursor->window, cursor->y, cursor->x);
    waddch(cursor->window, '*');
  }
  wrefresh(cursor->window);
}

void erase_card(struct card *card) {
  werase(card->frame->window);
  wbkgd(card->frame->window, WHITE_ON_GREEN);
  wrefresh(card->frame->window);
}

void erase_stack(struct stack *stack) {
  if (maneuvre_stack(stack)) {
    for (; stack; stack = stack->next) {
      erase_card(stack->card);
    }
  } else {
    erase_card(stack->card);
  }
}

void erase_cursor(struct cursor *cursor) {
  wdelch(cursor->window);
  wrefresh(cursor->window);
}
