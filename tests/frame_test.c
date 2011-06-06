#include <assert.h>
#include "test_helper.h"
#include "../src/frame.h"

void test_frame_init() {
  struct frame *frame;

  frame_malloc(&frame);
  frame_init(frame);

  assert(frame->window == NULL);
  assert(frame->begin_y == 0);
  assert(frame->begin_x == 0);

  frame_free(frame);
}

void test_frame_dup() {
  struct frame *frame_0, *frame_1;
  const int begin_y = 5, begin_x = 10;

  frame_malloc(&frame_0);
  frame_set(frame_0, begin_y, begin_x);
  frame_1 = frame_dup(frame_0);

  assert(frame_0 != frame_1);
  assert(frames_equal(frame_0, frame_1));
}

void test_frame_set() {
  struct frame *frame;
  int begin_y = 5;
  int begin_x = 10;

  frame_malloc(&frame);
  frame_init(frame);
  frame_set(frame, begin_y, begin_x);

  assert(frame->begin_y == begin_y);
  assert(frame->begin_x == begin_x);

  frame_free(frame);
}

void test_frame() {
  test_frame_init();
  test_frame_dup();
  test_frame_set();
}
