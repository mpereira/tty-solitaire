#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include "frame.h"

void allocate_frame(struct frame **frame) {
  if (!(*frame = malloc(sizeof(**frame)))) {
    fprintf(stderr, "%s: %s (%s:%d)\n", program_name, strerror(errno), __FILE__, __LINE__ - 1);
    exit(errno);
  }
}

void initialize_frame(struct frame *frame) {
  frame->shape   = NULL;
  frame->start_y = 0;
  frame->start_x = 0;
}

struct frame *duplicate_frame(struct frame *frame) {
  struct frame *new_frame;

  allocate_frame(&new_frame);
  set_frame(new_frame, frame->start_y, frame->start_x);

  return(new_frame);
}

void free_frame(struct frame *frame) {
  if (frame) {
    delwin(frame->shape);
  }
  free(frame);
}

void set_frame(struct frame *frame, int start_y, int start_x) {
  frame->start_y = start_y;
  frame->start_x = start_x;
  frame->shape = newwin(FRAME_HEIGHT,
                        FRAME_WIDTH,
                        frame->start_y,
                        frame->start_x);
}
