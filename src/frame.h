#ifndef TTY_SOLITAIRE_FRAME_H
#define TTY_SOLITAIRE_FRAME_H

#include <ncurses.h>

#define FRAME_WIDTH  7
#define FRAME_HEIGHT 5

struct frame {
  WINDOW *window;
  int    begin_y;
  int    begin_x;
};

void frame_malloc(struct frame **);
void frame_init(struct frame *);
void frame_free(struct frame *);
void frame_set(struct frame *, int, int);
struct frame *frame_dup(struct frame *);

#endif
