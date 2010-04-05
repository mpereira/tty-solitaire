#ifndef FRAME_H
#define FRAME_H

#include <ncurses.h>

#define FRAME_WIDTH  7
#define FRAME_HEIGHT 5

struct frame {
  WINDOW *shape;
  int    height;
  int    width;
  int    start_y;
  int    start_x;
};

struct frame *initialize_frame();
void delete_frame(struct frame *);
void set_frame(struct frame *, int, int);

#endif
