#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "display.h"
#include "curses.h"
#include "common.h"
#include "game.h"

bool stock_stack(struct stack *stack) {
  return(stack && stack->card && stack->card->frame &&
         (stack->card->frame->begin_y == STOCK_BEGIN_Y) &&
         (stack->card->frame->begin_x == STOCK_BEGIN_X));
}

bool waste_pile_stack(struct stack *stack) {
  return(stack && stack->card && stack->card->frame &&
         (stack->card->frame->begin_y == WASTE_PILE_BEGIN_Y) &&
         (stack->card->frame->begin_x == WASTE_PILE_BEGIN_X));
}

bool foundation_stack(struct stack *stack) {
  return(stack && stack->card && stack->card->frame &&
         stack->card->frame->begin_y == FOUNDATION_BEGIN_Y &&
         (stack->card->frame->begin_x == FOUNDATION_0_BEGIN_X ||
          stack->card->frame->begin_x == FOUNDATION_1_BEGIN_X ||
          stack->card->frame->begin_x == FOUNDATION_2_BEGIN_X ||
          stack->card->frame->begin_x == FOUNDATION_3_BEGIN_X));
}

bool maneuvre_stack(struct stack *stack) {
  return(stack && stack->card && stack->card->frame &&
         stack->card->frame->begin_y >= MANEUVRE_BEGIN_Y &&
         (stack->card->frame->begin_x == MANEUVRE_0_BEGIN_X ||
          stack->card->frame->begin_x == MANEUVRE_1_BEGIN_X ||
          stack->card->frame->begin_x == MANEUVRE_2_BEGIN_X ||
          stack->card->frame->begin_x == MANEUVRE_3_BEGIN_X ||
          stack->card->frame->begin_x == MANEUVRE_4_BEGIN_X ||
          stack->card->frame->begin_x == MANEUVRE_5_BEGIN_X ||
          stack->card->frame->begin_x == MANEUVRE_6_BEGIN_X));
}

bool valid_move(struct stack *origin, struct stack *destination) {
  if (stock_stack(origin)) {
    if (waste_pile_stack(destination)) {
      return(true);
    } else {
      return(false);
    }
  } else if (waste_pile_stack(origin)) {
    if (foundation_stack(destination) || maneuvre_stack(destination)) {
      return(true);
    } else {
      return(false);
    }
  } else if (foundation_stack(origin)) {
    if ((foundation_stack(destination) && origin != destination) || maneuvre_stack(destination)) {
      return(true);
    } else {
      return(false);
    }
  } else if (maneuvre_stack(origin)) {
    if ((maneuvre_stack(destination) && origin != destination) || foundation_stack(destination)) {
      return(true);
    } else {
      return(false);
    }
  } else {
    return(false);
  }
}

void move_card(struct stack **origin, struct stack **destination) {
  struct card *tmp;
  if ((tmp = pop(origin))) {
    int destination_y = (*destination)->card->frame->begin_y;
    int destination_x = (*destination)->card->frame->begin_x;
    if (!empty(*destination) && maneuvre_stack(*destination)) {
      destination_y++;
    }
    push(destination, tmp);
    set_frame((*destination)->card->frame, destination_y, destination_x);
  }
}

static void set_stacks_initial_coordinates(struct deck *deck) {
  set_frame(deck->stock->card->frame, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  set_frame(deck->waste_pile->card->frame, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  set_frame(deck->foundation_0->card->frame, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  set_frame(deck->foundation_1->card->frame, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  set_frame(deck->foundation_2->card->frame, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  set_frame(deck->foundation_3->card->frame, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  set_frame(deck->maneuvre_0->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  set_frame(deck->maneuvre_1->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  set_frame(deck->maneuvre_2->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  set_frame(deck->maneuvre_3->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  set_frame(deck->maneuvre_4->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  set_frame(deck->maneuvre_5->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  set_frame(deck->maneuvre_6->card->frame, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
}

static void fill_deck(struct deck *deck) {
  struct card *card[NUMBER_OF_CARDS];

  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    allocate_card(&(card[i]));
  }
  set_card(card[0], TWO, DIAMONDS, COVERED, 1, 1);
  set_card(card[1], TWO, SPADES, COVERED, 1, 1);
  set_card(card[2], TWO, HEARTS, COVERED, 1, 1);
  set_card(card[3], TWO, CLUBS, COVERED, 1, 1);
  set_card(card[4], THREE, DIAMONDS, COVERED, 1, 1);
  set_card(card[5], THREE, SPADES, COVERED, 1, 1);
  set_card(card[6], THREE, HEARTS, COVERED, 1, 1);
  set_card(card[7], THREE, CLUBS, COVERED, 1, 1);
  set_card(card[8], FOUR, DIAMONDS, COVERED, 1, 1);
  set_card(card[9], FOUR, SPADES, COVERED, 1, 1);
  set_card(card[10], FOUR, HEARTS, COVERED, 1, 1);
  set_card(card[11], FOUR, CLUBS, COVERED, 1, 1);
  set_card(card[12], FIVE, DIAMONDS, COVERED, 1, 1);
  set_card(card[13], FIVE, SPADES, COVERED, 1, 1);
  set_card(card[14], FIVE, HEARTS, COVERED, 1, 1);
  set_card(card[15], FIVE, CLUBS, COVERED, 1, 1);
  set_card(card[16], SIX, DIAMONDS, COVERED, 1, 1);
  set_card(card[17], SIX, SPADES, COVERED, 1, 1);
  set_card(card[18], SIX, HEARTS, COVERED, 1, 1);
  set_card(card[19], SIX, CLUBS, COVERED, 1, 1);
  set_card(card[20], SEVEN, DIAMONDS, COVERED, 1, 1);
  set_card(card[21], SEVEN, SPADES, COVERED, 1, 1);
  set_card(card[22], SEVEN, HEARTS, COVERED, 1, 1);
  set_card(card[23], SEVEN, CLUBS, COVERED, 1, 1);
  set_card(card[24], EIGHT, DIAMONDS, COVERED, 1, 1);
  set_card(card[25], EIGHT, SPADES, COVERED, 1, 1);
  set_card(card[26], EIGHT, HEARTS, COVERED, 1, 1);
  set_card(card[27], EIGHT, CLUBS, COVERED, 1, 1);
  set_card(card[28], NINE, DIAMONDS, COVERED, 1, 1);
  set_card(card[29], NINE, SPADES, COVERED, 1, 1);
  set_card(card[30], NINE, HEARTS, COVERED, 1, 1);
  set_card(card[31], NINE, CLUBS, COVERED, 1, 1);
  set_card(card[32], TEN, DIAMONDS, COVERED, 1, 1);
  set_card(card[33], TEN, SPADES, COVERED, 1, 1);
  set_card(card[34], TEN, HEARTS, COVERED, 1, 1);
  set_card(card[35], TEN, CLUBS, COVERED, 1, 1);
  set_card(card[36], JACK, DIAMONDS, COVERED, 1, 1);
  set_card(card[37], JACK, SPADES, COVERED, 1, 1);
  set_card(card[38], JACK, HEARTS, COVERED, 1, 1);
  set_card(card[39], JACK, CLUBS, COVERED, 1, 1);
  set_card(card[40], QUEEN, DIAMONDS, COVERED, 1, 1);
  set_card(card[41], QUEEN, SPADES, COVERED, 1, 1);
  set_card(card[42], QUEEN, HEARTS, COVERED, 1, 1);
  set_card(card[43], QUEEN, CLUBS, COVERED, 1, 1);
  set_card(card[44], KING, DIAMONDS, COVERED, 1, 1);
  set_card(card[45], KING, SPADES, COVERED, 1, 1);
  set_card(card[46], KING, HEARTS, COVERED, 1, 1);
  set_card(card[47], KING, CLUBS, COVERED, 1, 1);
  set_card(card[48], ACE, DIAMONDS, COVERED, 1, 1);
  set_card(card[49], ACE, SPADES, COVERED, 1, 1);
  set_card(card[50], ACE, HEARTS, COVERED, 1, 1);
  set_card(card[51], ACE, CLUBS, COVERED, 1, 1);

  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    push(&(deck->stock), card[i]);
  }
}

static void shuffle_deck(struct deck *deck) {
  struct card **card, tmp;
  int random;

  if (!(card = malloc(NUMBER_OF_CARDS * sizeof(*card)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }

  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    card[i] = pop(&(deck->stock));
  }

  srand(time(NULL));

  for (int i = 0; i < NUMBER_OF_CARDS - 1; i++) {
    random = i + (rand() % (NUMBER_OF_CARDS) - i);
    tmp = *card[i];
    *card[i] = (*card[random]);
    *card[random] = tmp;
  }

  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    push(&(deck->stock), card[i]);
  }
}

static void deal_cards(struct deck *deck) {
  move_card(&(deck->stock), &(deck->maneuvre_0));
  expose_card(deck->maneuvre_0->card);
  move_card(&(deck->stock), &(deck->maneuvre_1));
  move_card(&(deck->stock), &(deck->maneuvre_2));
  move_card(&(deck->stock), &(deck->maneuvre_3));
  move_card(&(deck->stock), &(deck->maneuvre_4));
  move_card(&(deck->stock), &(deck->maneuvre_5));
  move_card(&(deck->stock), &(deck->maneuvre_6));

  move_card(&(deck->stock), &(deck->maneuvre_1));
  expose_card(deck->maneuvre_1->card);
  move_card(&(deck->stock), &(deck->maneuvre_2));
  move_card(&(deck->stock), &(deck->maneuvre_3));
  move_card(&(deck->stock), &(deck->maneuvre_4));
  move_card(&(deck->stock), &(deck->maneuvre_5));
  move_card(&(deck->stock), &(deck->maneuvre_6));

  move_card(&(deck->stock), &(deck->maneuvre_2));
  expose_card(deck->maneuvre_2->card);
  move_card(&(deck->stock), &(deck->maneuvre_3));
  move_card(&(deck->stock), &(deck->maneuvre_4));
  move_card(&(deck->stock), &(deck->maneuvre_5));
  move_card(&(deck->stock), &(deck->maneuvre_6));

  move_card(&(deck->stock), &(deck->maneuvre_3));
  expose_card(deck->maneuvre_3->card);
  move_card(&(deck->stock), &(deck->maneuvre_4));
  move_card(&(deck->stock), &(deck->maneuvre_5));
  move_card(&(deck->stock), &(deck->maneuvre_6));

  move_card(&(deck->stock), &(deck->maneuvre_4));
  expose_card(deck->maneuvre_4->card);
  move_card(&(deck->stock), &(deck->maneuvre_5));
  move_card(&(deck->stock), &(deck->maneuvre_6));

  move_card(&(deck->stock), &(deck->maneuvre_5));
  expose_card(deck->maneuvre_5->card);
  move_card(&(deck->stock), &(deck->maneuvre_6));

  move_card(&(deck->stock), &(deck->maneuvre_6));
  expose_card(deck->maneuvre_6->card);
}

void greet_player() {
  mvprintw(10, 27, "Welcome to tty-solitaire.");
  mvprintw(11, 8, "Move with \u2190\u2191\u2192\u2193 or hjkl. Use the space bar to mark and move cards.");
  mvprintw(12, 19, "Press the space bar to play or q to quit.");
}

void initialize_game() {
  clear_screen();

  allocate_cursor(&cursor);
  initialize_cursor(cursor);

  allocate_deck(&deck);
  initialize_deck(deck);

  set_stacks_initial_coordinates(deck);
  fill_deck(deck);
  shuffle_deck(deck);
  deal_cards(deck);

  draw_cursor(cursor);
  draw_deck(deck);
}

void end_game() {
  free_deck(deck);
  free_cursor(cursor);
}
