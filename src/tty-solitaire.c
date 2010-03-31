#include <ncurses.h>
#include <malloc.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

#define CARD_FRAME_WIDTH  7
#define CARD_FRAME_HEIGHT 5

enum suit {
  BLANK    = -1,
  DIAMONDS = 0,
  SPADES   = 1,
  HEARTS   = 2,
  CLUBS    = 3
};

enum value {
  NONE  = -1,
  TWO   = 2,
  THREE = 3,
  FOUR  = 4,
  FIVE  = 5,
  SIX   = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE  = 9,
  TEN   = 10,
  JACK  = 11,
  QUEEN = 12,
  KING  = 13,
  ACE   = 14
};

struct card_frame {
  WINDOW *shape;
  int    height;
  int    width;
  int    start_y;
  int    start_x;
};

struct card {
  struct card_frame *frame;
  enum value        value;
  enum suit         suit;
  char              exposed;
};

WINDOW *initialize_shape();
struct card_frame *initialize_card_frame();
struct card *initialize_card();
void draw_card(struct card *);
void set_card_frame(struct card_frame *, int, int);
void set_card_attributes(struct card *, enum value, enum suit, char);
void set_card(struct card *, enum value, enum suit, char, int, int);
void delete_card(struct card *);

int main(int argc, const char *argv[]) {
  char message[] = "Welcome to tty-solitaire.";
  int ch;
  int row_number, column_number;
  struct card *card = NULL;

  initscr();                /* initialize the terminal in curses mode */
  raw();                    /* disable line buffers                   */
  noecho();                 /* character echo is unnecessary          */
  keypad(stdscr, TRUE);     /* enable F and arrow keys                */

  getmaxyx(stdscr, row_number, column_number);
  mvprintw(row_number / 2 - 1,
           (column_number - strlen(message)) / 2,
           "%s\n",
           message);

  card = initialize_card();

  set_card(card, KING, CLUBS, TRUE, 1, 1);

  draw_card(card);

  while ((ch = getch()) != KEY_F(1)) {
    switch(ch) {
      case KEY_LEFT:
      case 'h':
        draw_card(card);
        break;
      case KEY_RIGHT:
      case 'l':
        draw_card(card);
        break;
      case KEY_UP:
      case 'k':
        draw_card(card);
        break;
      case KEY_DOWN:
      case 'j':
        draw_card(card);
        break;
    }
  }

  endwin();
  puts("Game finished.");

  return 0;
}

WINDOW *initialize_shape() {
  WINDOW *shape;

  shape = malloc(sizeof(shape));

  return(shape);
}

struct card_frame *initialize_card_frame() {
  struct card_frame *card_frame = NULL;

  card_frame = malloc(sizeof(card_frame));

  card_frame->shape  = initialize_shape();
  card_frame->height  = CARD_FRAME_HEIGHT;
  card_frame->width   = CARD_FRAME_WIDTH;
  card_frame->start_y = 0;
  card_frame->start_x = 0;

  return(card_frame);
}

struct card *initialize_card() {
  struct card *card = NULL;

  card = malloc(sizeof(card));

  card->frame   = initialize_card_frame();
  card->value   = NONE;
  card->suit    = NONE;
  card->exposed = FALSE;

  return(card);
}

void draw_card(struct card *card) {
  box(card->frame->shape, 0, 0);
  wrefresh(card->frame->shape);
}

void set_card_frame(struct card_frame *card_frame,
                    int start_y,
                    int start_x) {
  card_frame->start_y = start_y;
  card_frame->start_x = start_x;
  card_frame->shape = newwin(card_frame->height,
                             card_frame->width,
                             card_frame->start_y,
                             card_frame->start_x);

  return;
}

void set_card_attributes(struct card *card,
                        enum value value,
                        enum suit suit,
                        char exposed) {
  card->value = value;
  card->suit = suit;
  card->exposed = exposed;

  return;
}

void set_card(struct card *card,
              enum value value,
              enum suit suit,
              char exposed,
              int start_y,
              int start_x) {
  set_card_attributes(card, value, suit, exposed);
  set_card_frame(card->frame, start_y, start_x);

  return;
}

void delete_card(struct card *card) {
  free(card->frame->shape);
  free(card->frame);
  free(card);

  return;
}
