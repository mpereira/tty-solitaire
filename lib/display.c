#include <ncurses.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include "display.h"

void init_curses() {
  setlocale(LC_ALL, "");    /* supporting unicode characters          */
  initscr();                /* initialize the terminal in curses mode */
  raw();                    /* disable line buffers                   */
  noecho();                 /* character echo is unnecessary          */
  keypad(stdscr, TRUE);     /* enable F and arrow keys                */
  start_color();

  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
}

void draw_empty_stacks() {
  WINDOW **empty_stack;

  empty_stack = malloc(EMPTY_STACKS_NUMBER * sizeof(**empty_stack));

  empty_stack[0] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 1, 1);
  empty_stack[1] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 1, 9);
  empty_stack[2] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 1, 25);
  empty_stack[3] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 1, 33);
  empty_stack[4] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 1, 41);
  empty_stack[5] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 1, 49);
  empty_stack[6] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 1);
  empty_stack[7] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 9);
  empty_stack[8] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 17);
  empty_stack[9] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 25);
  empty_stack[10] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 33);
  empty_stack[11] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 41);
  empty_stack[12] = newwin(FRAME_HEIGHT, FRAME_WIDTH, 7, 49);

  for (int i = 0; i < EMPTY_STACKS_NUMBER; i++) {
    box(empty_stack[i], 0, 0);
    wrefresh(empty_stack[i]);
    delwin(empty_stack[i]);
  }

  free(empty_stack);

  return;
}

void initialize_game() {
  struct deck *deck = NULL;

  draw_empty_stacks();
  allocate_deck(&deck);
  initialize_deck(deck);
  delete_deck(deck);

  return;
}

char *card_suit(enum suit suit) {
  char *card_suit;

  card_suit = malloc(5 * sizeof(*card_suit));

  switch(suit) {
    case DIAMONDS: strcpy(card_suit, DIAMONDS_SYMBOL); break;
    case SPADES:   strcpy(card_suit, SPADES_SYMBOL);   break;
    case HEARTS:   strcpy(card_suit, HEARTS_SYMBOL);   break;
    case CLUBS:    strcpy(card_suit, CLUBS_SYMBOL);    break;
    default:       strcpy(card_suit, "?");
  }

  return(card_suit);
}

char *card_value(enum value value) {
  char *card_value;

  card_value = malloc(2 * sizeof(*card_value));

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

void draw_value(struct card *card) {
  mvwprintw(card->frame->shape, 0, 0, card_value(card->value));
  mvwprintw(card->frame->shape, 4, 6, card_value(card->value));

  return;
}

void draw_suit(struct card *card) {
  if (card->suit % 2 == 0) {
    wattron(card->frame->shape, COLOR_PAIR(RED_ON_WHITE));
    mvwprintw(card->frame->shape, 0, 1, card_suit(card->suit));
    mvwprintw(card->frame->shape, 4, 5, card_suit(card->suit));
    wattroff(card->frame->shape, COLOR_PAIR(RED_ON_WHITE));
  } else {
    wattron(card->frame->shape, COLOR_PAIR(BLACK_ON_WHITE));
    mvwprintw(card->frame->shape, 0, 1, card_suit(card->suit));
    mvwprintw(card->frame->shape, 4, 5, card_suit(card->suit));
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
  if (card->face == EXPOSED) {
    draw_front(card);
  } else {
    draw_back(card);
  }

  return;
}
