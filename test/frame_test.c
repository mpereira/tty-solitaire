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

void test_duplicate_frame() {
  struct frame *frame_0, *frame_1;
  const int start_y = 5, start_x = 10;

  allocate_frame(&frame_0);
  set_frame(frame_0, start_y, start_x);
  frame_1 = duplicate_frame(frame_0);

  assert(frame_0 != frame_1);
  assert(frames_equal(frame_0, frame_1));

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
  test_duplicate_frame();
  test_set_frame();

  return;
}
