#include <assert.h>
#include "test_helper.h"
#include "../lib/frame.h"

void test_initialize_frame() {
  struct frame *frame;

  allocate_frame(&frame);
  initialize_frame(frame);

  assert(frame->shape == NULL);
  assert(frame->begin_y == 0);
  assert(frame->begin_x == 0);

  free_frame(frame);
}

void test_duplicate_frame() {
  struct frame *frame_0, *frame_1;
  const int begin_y = 5, begin_x = 10;

  allocate_frame(&frame_0);
  set_frame(frame_0, begin_y, begin_x);
  frame_1 = duplicate_frame(frame_0);

  assert(frame_0 != frame_1);
  assert(frames_equal(frame_0, frame_1));
}

void test_set_frame() {
  struct frame *frame;
  int begin_y = 5;
  int begin_x = 10;

  allocate_frame(&frame);
  initialize_frame(frame);
  set_frame(frame, begin_y, begin_x);

  assert(frame->begin_y == begin_y);
  assert(frame->begin_x == begin_x);

  free_frame(frame);
}

void test_frame() {
  test_initialize_frame();
  test_duplicate_frame();
  test_set_frame();
}
