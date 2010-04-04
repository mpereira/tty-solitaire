#include <ncurses.h>
#include <malloc.h>
#include "frame.h"

struct frame *initialize_frame() {
  struct frame *frame = NULL;

  frame = malloc(sizeof(*frame));

  frame->shape  = NULL;
  frame->height  = FRAME_HEIGHT;
  frame->width   = FRAME_WIDTH;
  frame->start_y = 0;
  frame->start_x = 0;

  return(frame);
}

void delete_frame(struct frame *frame) {
  delwin(frame->shape);
  free(frame);

  return;
}

void set_frame(struct frame *frame, int start_y, int start_x) {
  frame->start_y = start_y;
  frame->start_x = start_x;
  frame->shape = newwin(frame->height,
                        frame->width,
                        frame->start_y,
                        frame->start_x);

  return;
}
