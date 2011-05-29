#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>
#include "game.h"
#include "display.h"
#include "common.h"

static char *card_suit(enum suit suit) {
  char *card_suit;

  if (!(card_suit = malloc(4 * sizeof(*card_suit)))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
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
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
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

void draw_value(struct card *card) {
  mvwprintw(card->frame->window, 0, 0, card_value(card->value));
  mvwprintw(card->frame->window,
            4,
            6 - (strlen(card_value(card->value)) - 1),
            card_value(card->value));
}

void draw_suit(struct card *card) {
  if (card->suit % 2 == 0) {
    wattron(card->frame->window, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattron(card->frame->window, COLOR_PAIR(BLACK_ON_WHITE));
  }
  mvwprintw(card->frame->window, 0, 1 + (strlen(card_value(card->value) + 1)),
    card_suit(card->suit));
  mvwprintw(card->frame->window, 4, 5 - (strlen(card_value(card->value) + 1)),
    card_suit(card->suit));
  if (card->suit % 2 == 0) {
    wattroff(card->frame->window, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattroff(card->frame->window, COLOR_PAIR(BLACK_ON_WHITE));
  }
}

void draw_front(struct card *card) {
  wbkgd(card->frame->window, COLOR_PAIR(BLACK_ON_WHITE));
  draw_value(card);
  draw_suit(card);
}

void draw_back(struct card *card) {
  wbkgd(card->frame->window, COLOR_PAIR(WHITE_ON_BLUE));
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
  erase_stack(stack);
  if (empty(stack)) {
    box(stack->card->frame->window, 0, 0);
    wrefresh(stack->card->frame->window);
  } else {
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
}

void draw_cursor(struct cursor *cursor) {
  mvwaddch(cursor->window, cursor->y, cursor->x, '*');
  wrefresh(cursor->window);
}

void erase_cursor(struct cursor *cursor) {
  mvwdelch(cursor->window, cursor->y, cursor->x);
}
