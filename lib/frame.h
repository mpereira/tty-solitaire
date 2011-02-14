#ifndef FRAME_H
#define FRAME_H

#include <ncurses.h>

#define FRAME_WIDTH  7
#define FRAME_HEIGHT 5

struct frame {
  WINDOW *shape;
  int    start_y;
  int    start_x;
};

extern const char *program_name;

void allocate_frame(struct frame **);
void initialize_frame(struct frame *);
void free_frame(struct frame *);
void set_frame(struct frame *, int, int);

#endif
