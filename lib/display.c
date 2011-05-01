#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>
#include "game.h"
#include "display.h"

static char *card_suit(enum suit suit) {
  char *card_suit;

  if (!(card_suit = malloc(5 * sizeof(*card_suit)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }

  switch(suit) {
  case DIAMONDS: strcpy(card_suit, DIAMONDS_SYMBOL); break;
  case SPADES:   strcpy(card_suit, SPADES_SYMBOL);   break;
  case HEARTS:   strcpy(card_suit, HEARTS_SYMBOL);   break;
  case CLUBS:    strcpy(card_suit, CLUBS_SYMBOL);    break;
  default:       strcpy(card_suit, "?");
  }

  return(card_suit);
}

static char *card_value(enum value value) {
  char *card_value;

  if (!(card_value = malloc(2 * sizeof(*card_value)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }

  switch(value) {
  case TWO:   card_value = "2";  break;
  case THREE: card_value = "3";  break;
  case FOUR:  card_value = "4";  break;
  case FIVE:  card_value = "5";  break;
  case SIX:   card_value = "6";  break;
  case SEVEN: card_value = "7";  break;
  case EIGHT: card_value = "8";  break;
  case NINE:  card_value = "9";  break;
  case TEN:   card_value = "10"; break;
  case JACK:  card_value = "J";  break;
  case QUEEN: card_value = "Q";  break;
  case KING:  card_value = "K";  break;
  case ACE:   card_value = "A";  break;
  default:    card_value = "?";
  }

  return(card_value);
}

void erase_stack(struct stack *stack) {
  WINDOW *empty_stack = NULL;

  wbkgd(stack->card->frame->shape, WHITE_ON_GREEN);
  wrefresh(stack->card->frame->shape);
  empty_stack = newwin(FRAME_HEIGHT,
                       FRAME_WIDTH,
                       stack->card->frame->start_y,
                       stack->card->frame->start_x);
  box(empty_stack, 0, 0);
  wrefresh(empty_stack);
  delwin(empty_stack);

  return;
}

void draw_empty_stacks() {
  WINDOW **empty_stack;

  if (!(empty_stack = malloc(EMPTY_STACKS_NUMBER * sizeof(**empty_stack)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }

  empty_stack[0] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          STOCK_STARTING_Y,
                          STOCK_STARTING_X);
  empty_stack[1] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          WASTE_PILE_STARTING_Y,
                          WASTE_PILE_STARTING_X);
  empty_stack[2] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          FOUNDATION_STARTING_Y,
                          FOUNDATION_0_STARTING_X);
  empty_stack[3] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          FOUNDATION_STARTING_Y,
                          FOUNDATION_1_STARTING_X);
  empty_stack[4] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          FOUNDATION_STARTING_Y,
                          FOUNDATION_2_STARTING_X);
  empty_stack[5] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          FOUNDATION_STARTING_Y,
                          FOUNDATION_3_STARTING_X);
  empty_stack[6] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          MANEUVRE_STARTING_Y,
                          MANEUVRE_0_STARTING_X);
  empty_stack[7] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          MANEUVRE_STARTING_Y,
                          MANEUVRE_1_STARTING_X);
  empty_stack[8] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          MANEUVRE_STARTING_Y,
                          MANEUVRE_2_STARTING_X);
  empty_stack[9] = newwin(FRAME_HEIGHT,
                          FRAME_WIDTH,
                          MANEUVRE_STARTING_Y,
                          MANEUVRE_3_STARTING_X);
  empty_stack[10] = newwin(FRAME_HEIGHT,
                           FRAME_WIDTH,
                           MANEUVRE_STARTING_Y,
                           MANEUVRE_4_STARTING_X);
  empty_stack[11] = newwin(FRAME_HEIGHT,
                           FRAME_WIDTH,
                           MANEUVRE_STARTING_Y,
                           MANEUVRE_5_STARTING_X);
  empty_stack[12] = newwin(FRAME_HEIGHT,
                           FRAME_WIDTH,
                           MANEUVRE_STARTING_Y,
                           MANEUVRE_6_STARTING_X);

  for (int i = 0; i < EMPTY_STACKS_NUMBER; i++) {
    box(empty_stack[i], 0, 0);
    wrefresh(empty_stack[i]);
    delwin(empty_stack[i]);
  }

  free(empty_stack);

  return;
}

void draw_value(struct card *card) {
  mvwprintw(card->frame->shape, 0, 0, card_value(card->value));
  mvwprintw(card->frame->shape,
            4,
            6 - (strlen(card_value(card->value)) - 1),
            card_value(card->value));

  return;
}

void draw_suit(struct card *card) {
  if (card->suit % 2 == 0) {
    wattron(card->frame->shape, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattron(card->frame->shape, COLOR_PAIR(BLACK_ON_WHITE));
  }
  mvwprintw(card->frame->shape, 0, 1 + (strlen(card_value(card->value) + 1)),
    card_suit(card->suit));
  mvwprintw(card->frame->shape, 4, 5 - (strlen(card_value(card->value) + 1)),
    card_suit(card->suit));
  if (card->suit % 2 == 0) {
    wattroff(card->frame->shape, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattroff(card->frame->shape, COLOR_PAIR(BLACK_ON_WHITE));
  }

  return;
}

void draw_front(struct card *card) {
  wbkgd(card->frame->shape, COLOR_PAIR(BLACK_ON_WHITE));
  draw_value(card);
  draw_suit(card);

  return;
}

void draw_back(struct card *card) {
  wbkgd(card->frame->shape, COLOR_PAIR(WHITE_ON_BLUE));

  return;
}

void draw_card(struct card *card) {
  mvwin(card->frame->shape, card->frame->start_y, card->frame->start_x);
  if (card->face == EXPOSED) {
    draw_front(card);
  } else {
    draw_back(card);
  }
  wrefresh(card->frame->shape);

  return;
}

void draw_stack(struct stack *stack) {
  if (!empty(stack)) {
    if (maneuvre_stack(stack)) {
      struct stack *reversed_stack = reverse(stack);

      for (struct stack *i = reversed_stack; i; i = i->next) {
        draw_card(i->card);
      }
    } else {
      draw_card(stack->card);
    }
  }
}

void draw_deck(struct deck *deck) {
  draw_stack(deck->stock);
  draw_stack(deck->waste_pile);

  draw_stack(deck->foundation_0);
  draw_stack(deck->foundation_1);
  draw_stack(deck->foundation_2);
  draw_stack(deck->foundation_3);

  draw_stack(deck->maneuvre_0);
  draw_stack(deck->maneuvre_1);
  draw_stack(deck->maneuvre_2);
  draw_stack(deck->maneuvre_3);
  draw_stack(deck->maneuvre_4);
  draw_stack(deck->maneuvre_5);
  draw_stack(deck->maneuvre_6);

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
