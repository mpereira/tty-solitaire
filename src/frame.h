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

void allocate_frame(struct frame **);
void initialize_frame(struct frame *);
void free_frame(struct frame *);
void set_frame(struct frame *, int, int);
struct frame *duplicate_frame(struct frame *);

#endif
