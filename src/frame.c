#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "frame.h"
#include "common.h"

void frame_malloc(struct frame **frame) {
  if (!(*frame = malloc(sizeof(**frame)))) {
    tty_solitaire_generic_error(errno, __FILE__, __LINE__);
  }
  (*frame)->window = newwin(FRAME_HEIGHT, FRAME_WIDTH, 0, 0);
}

void frame_init(struct frame *frame) {
  frame->begin_y = 0;
  frame->begin_x = 0;
}

void frame_free(struct frame *frame) {
  delwin(frame->window);
  free(frame);
}

void frame_set(struct frame *frame, int begin_y, int begin_x) {
  frame->begin_y = begin_y;
  frame->begin_x = begin_x;
  mvwin(frame->window, begin_y, begin_x);
}

struct frame *frame_dup(struct frame *frame) {
  struct frame *new_frame;

  frame_malloc(&new_frame);
  frame_set(new_frame, frame->begin_y, frame->begin_x);

  return(new_frame);
}
