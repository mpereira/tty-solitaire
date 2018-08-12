#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <assert.h>

#include "game.h"
#include "card.h"
#include "stack.h"
#include "deck.h"
#include "gui.h"
#include "cursor.h"
#include "common.h"

static int foundation_begin_x(int x) {
  switch (x) {
  case 0: return(FOUNDATION_0_BEGIN_X);
  case 1: return(FOUNDATION_1_BEGIN_X);
  case 2: return(FOUNDATION_2_BEGIN_X);
  case 3: return(FOUNDATION_3_BEGIN_X);
  default:
    endwin();
    game_end();
    assert(false && "invalid stack");
  }
}

static int maneuvre_begin_x(int x) {
  switch (x) {
  case 0: return(MANEUVRE_0_BEGIN_X);
  case 1: return(MANEUVRE_1_BEGIN_X);
  case 2: return(MANEUVRE_2_BEGIN_X);
  case 3: return(MANEUVRE_3_BEGIN_X);
  case 4: return(MANEUVRE_4_BEGIN_X);
  case 5: return(MANEUVRE_5_BEGIN_X);
  case 6: return(MANEUVRE_6_BEGIN_X);
  default:
    endwin();
    game_end();
    assert(false && "maneuvre_begin_x called x < 0 || x > 6");
  }
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

bool stock_stack(struct stack *stack) {
  return((stack->card->frame->begin_y == STOCK_BEGIN_Y) &&
           (stack->card->frame->begin_x == STOCK_BEGIN_X));
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
      if (stack_empty(destination)) {
        if (origin->card->value == ACE) {
          return(true);
        }
      } else if (origin->card->suit == destination->card->suit &&
                    origin->card->value == destination->card->value + 1) {
          return(true);
      }
    } else if (maneuvre_stack(destination)) {
      if (stack_empty(destination)) {
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
  if ((tmp = stack_pop(origin))) {
    int destination_y = (*destination)->card->frame->begin_y;
    int destination_x = (*destination)->card->frame->begin_x;
    if (!stack_empty(*destination) && maneuvre_stack(*destination)) {
      destination_y++;
    }
    stack_push(destination, tmp);
    frame_set((*destination)->card->frame, destination_y, destination_x);
  }
}

void move_block(struct stack **origin, struct stack **destination, int block_size) {
  struct stack *tmp;
  stack_malloc(&tmp);
  stack_init(tmp);
  for (int i = 0; i < block_size; i++) {
    stack_push(&tmp, stack_pop(origin));
  }
  for (int i = 0; i < block_size; i++) {
    move_card(&tmp, destination);
  }
  if (stack_length(*destination) > 1) {
    cursor->y += block_size;
  }
  stack_free(tmp);
}

static void fill_deck(struct deck *deck) {
  struct card *card[NUMBER_OF_CARDS];

  for (int i = ACE; i <= KING; i++) {
    for (int j = DIAMONDS; j <= CLUBS; j++) {
      int index = 4 * (i - ACE) + j;
      card_malloc(&(card[index]));
      card_set(card[index], i, j, COVERED, 1, 1);
      stack_push(&(deck->stock), card[index]);
    }
  }
}

static void shuffle_deck(struct deck *deck) {
  struct card **card, tmp;
  int random;

  if (!(card = malloc(NUMBER_OF_CARDS * sizeof(*card)))) {
    tty_solitaire_generic_error(errno, __FILE__, __LINE__);
  }
  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    card[i] = stack_pop(&(deck->stock));
  }
  srand(time(NULL));
  for (int i = 0; i < NUMBER_OF_CARDS - 1; i++) {
    random = i + (rand() % (NUMBER_OF_CARDS) - i);
    tmp = *card[i];
    *card[i] = (*card[random]);
    *card[random] = tmp;
  }
  for (int i = 0; i < NUMBER_OF_CARDS; i++) {
    stack_push(&(deck->stock), card[i]);
  }
}

static void deal_cards(struct deck *deck) {
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    move_card(&(deck->stock), &(deck->maneuvre[i]));
    card_expose(deck->maneuvre[i]->card);
    for (int j = i + 1; j < MANEUVRE_STACKS_NUMBER; j++) {
      move_card(&(deck->stock), &(deck->maneuvre[j]));
    }
  }
}

void game_init(struct game *game, int passes_through_deck) {
  cursor_malloc(&cursor);
  cursor_init(cursor);
  deck_malloc(&deck);
  deck_init(deck);

  /* Setting initial stacks' coordinates. */
  frame_set(deck->stock->card->frame, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  frame_set(deck->waste_pile->card->frame, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  for (int i = 0; i < FOUNDATION_STACKS_NUMBER; i++) {
    frame_set(deck->foundation[i]->card->frame, FOUNDATION_BEGIN_Y, foundation_begin_x(i));
  }
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    frame_set(deck->maneuvre[i]->card->frame, MANEUVRE_BEGIN_Y, maneuvre_begin_x(i));
  }

  fill_deck(deck);
  shuffle_deck(deck);
  deal_cards(deck);

  draw_cursor(cursor);
  draw_deck(deck);

  game->passes_through_deck_left = passes_through_deck;
}

void game_end() {
  cursor_free(cursor);
  deck_free(deck);
}

bool game_won() {
  // If any card in the maneuvre stacks is covered, game is not won.
  for (int i = 0; i < MANEUVRE_STACKS_NUMBER; i++) {
    for (struct stack *j = deck->maneuvre[i]; j!= NULL; j = j->next) {
      if (j->card->face == COVERED) {
        return(false);
      }
    }
  }

  // If the stock pile or the waste pile aren't empty, game is not won.
  if (!stack_empty(deck->stock) || !stack_empty(deck->waste_pile)) {
    return(false);
  }

  return(true);
}
