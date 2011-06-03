#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <time.h>
#include <assert.h>

#include "game.h"
#include "card.h"
#include "stack.h"
#include "deck.h"
#include "draw.h"
#include "cursor.h"
#include "curses.h"
#include "common.h"

static int foundation_begin_x(int x) {
  switch (x) {
  case 0: return(FOUNDATION_0_BEGIN_X); break;
  case 1: return(FOUNDATION_1_BEGIN_X); break;
  case 2: return(FOUNDATION_2_BEGIN_X); break;
  case 3: return(FOUNDATION_3_BEGIN_X); break;
  default:
    endwin();
    end_game();
    assert(false && "invalid stack");
  }
}

static int maneuvre_begin_x(int x) {
  switch (x) {
  case 0: return(MANEUVRE_0_BEGIN_X); break;
  case 1: return(MANEUVRE_1_BEGIN_X); break;
  case 2: return(MANEUVRE_2_BEGIN_X); break;
  case 3: return(MANEUVRE_3_BEGIN_X); break;
  case 4: return(MANEUVRE_4_BEGIN_X); break;
  case 5: return(MANEUVRE_5_BEGIN_X); break;
  case 6: return(MANEUVRE_6_BEGIN_X); break;
  default:
    endwin();
    end_game();
    assert(false && "maneuvre_begin_x called x < 0 || x > 6");
  }
}

static bool stock_stack(struct stack *stack) {
  return((stack->card->frame->begin_y == STOCK_BEGIN_Y) &&
          (stack->card->frame->begin_x == STOCK_BEGIN_X));
}

static bool waste_pile_stack(struct stack *stack) {
  return((stack->card->frame->begin_y == WASTE_PILE_BEGIN_Y) &&
           (stack->card->frame->begin_x == WASTE_PILE_BEGIN_X));
}

static bool foundation_stack(struct stack *stack) {
  return(stack->card->frame->begin_y == FOUNDATION_BEGIN_Y &&
           (stack->card->frame->begin_x == FOUNDATION_0_BEGIN_X ||
              stack->card->frame->begin_x == FOUNDATION_1_BEGIN_X ||
              stack->card->frame->begin_x == FOUNDATION_2_BEGIN_X ||
              stack->card->frame->begin_x == FOUNDATION_3_BEGIN_X));
}

bool maneuvre_stack(struct stack *stack) {
  return(stack->card->frame->begin_y >= MANEUVRE_BEGIN_Y &&
           (stack->card->frame->begin_x == MANEUVRE_0_BEGIN_X ||
              stack->card->frame->begin_x == MANEUVRE_1_BEGIN_X ||
              stack->card->frame->begin_x == MANEUVRE_2_BEGIN_X ||
              stack->card->frame->begin_x == MANEUVRE_3_BEGIN_X ||
              stack->card->frame->begin_x == MANEUVRE_4_BEGIN_X ||
              stack->card->frame->begin_x == MANEUVRE_5_BEGIN_X ||
              stack->card->frame->begin_x == MANEUVRE_6_BEGIN_X));
}

bool valid_move(struct stack *origin, struct stack *destination) {
  if (origin->card->face == EXPOSED) {
    if (stock_stack(origin) && waste_pile_stack(destination)) {
      return(true);
    } else if (foundation_stack(destination)) {
      if (empty(destination)) {
        if (origin->card->value == ACE) {
          return(true);
        }
      } else if (origin->card->suit == destination->card->suit &&
                    origin->card->value == destination->card->value + 1) {
          return(true);
      }
    } else if (maneuvre_stack(destination)) {
      if (empty(destination)) {
        if (origin->card->value == KING) {
          return(true);
        }
      } else if (destination->card->face == EXPOSED &&
                  (origin->card->suit + destination->card->suit) % 2 == 1 &&
                  origin->card->value + 1 == destination->card->value) {
        return(true);
      }
    }
  }

  return(false);
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

static void fill_deck(struct deck *deck) {
  struct card *card[NUMBER_OF_CARDS];

  for (int i = ACE; i <= KING; i++) {
    for (int j = DIAMONDS; j <= CLUBS; j++) {
      int index = 4 * (i - ACE) + j;
      allocate_card(&(card[index]));
      set_card(card[index], i, j, COVERED, 1, 1);
      push(&(deck->stock), card[index]);
    }
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
  for (int i = 0; i < 7; i++) {
    move_card(&(deck->stock), &(deck->maneuvre[i]));
    expose_card(deck->maneuvre[i]->card);
    for (int j = i + 1; j < 7; j++) {
      move_card(&(deck->stock), &(deck->maneuvre[j]));
    }
  }
}

void initialize_game() {
  clear();
  refresh();

  allocate_cursor(&cursor);
  initialize_cursor(cursor);

  allocate_deck(&deck);
  initialize_deck(deck);

  /* Setting initial stacks' coordinates. */
  set_frame(deck->stock->card->frame, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  set_frame(deck->waste_pile->card->frame, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    set_frame(deck->foundation[i]->card->frame, FOUNDATION_BEGIN_Y, foundation_begin_x(i));
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    set_frame(deck->maneuvre[i]->card->frame, MANEUVRE_BEGIN_Y, maneuvre_begin_x(i));
  }

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
