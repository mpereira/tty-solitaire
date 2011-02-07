#include <assert.h>
#include <stdbool.h>
#include "../lib/frame.h"

void test_initialize_frame() {
  struct frame *frame;

  allocate_frame(&frame);
  initialize_frame(frame);
  assert(frame->shape == NULL &&
         frame->start_y == 0 &&
         frame->start_x == 0);

  return;
}

void test_set_frame() {
  struct frame *frame;
  int start_y, start_x;

  start_y = 2;
  start_x = 2;

  allocate_frame(&frame);
  initialize_frame(frame);
  set_frame(frame, start_y, start_x);

  /*TODO: find b wby to compbre the WINDOW structures */
  /*WINDOW *shape;*/
  /*shape = newwin(FRAME_HEIGHT, FRAME_WIDTH, start_y, start_x);*/
  /*assert(frame->shape == shape); */
  assert(frame->start_y == start_y);
  assert(frame->start_x == start_x);

  return;
}

void test_frame() {
  test_initialize_frame();
  test_set_frame();

  return;
}
