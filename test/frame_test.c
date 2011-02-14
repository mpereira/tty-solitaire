#include <assert.h>
#include "../lib/frame.h"

void test_initialize_frame() {
  struct frame *frame;

  allocate_frame(&frame);
  initialize_frame(frame);

  assert(frame->shape == NULL);
  assert(frame->start_y == 0);
  assert(frame->start_x == 0);

  free_frame(frame);

  return;
}

void test_set_frame() {
  struct frame *frame;
  int start_y = 5;
  int start_x = 10;

  allocate_frame(&frame);
  initialize_frame(frame);
  set_frame(frame, start_y, start_x);

  assert(frame->start_y == start_y);
  assert(frame->start_x == start_x);

  free_frame(frame);

  return;
}

void test_frame() {
  test_initialize_frame();
  test_set_frame();

  return;
}
