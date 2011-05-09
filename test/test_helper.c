#include "test_helper.h"

bool frames_equal(struct frame *frame_0, struct frame *frame_1) {
  if (frame_0 && frame_1) {
    return(frame_0->begin_y == frame_1->begin_y &&
           frame_0->begin_x == frame_1->begin_x);
  } else if ((frame_0 && !frame_1) || (!frame_0 && frame_1)) {
    return(false);
  } else {
    return(true);
  }
}

bool cards_equal(struct card *card_0, struct card *card_1) {
  if (card_0 && card_1) {
    return(frames_equal(card_0->frame, card_1->frame) &&
           card_0->value == card_1->value &&
           card_0->suit == card_1->suit &&
           card_0->face == card_1->face);
  } else if ((card_0 && !card_1) || (!card_0 && card_1)) {
    return(false);
  } else {
    return(true);
  }
}

bool stacks_equal(struct stack *stack_0, struct stack *stack_1) {
  if (stack_0 && stack_1) {
    return(cards_equal(stack_0->card, stack_1->card) &&
           stacks_equal(stack_0->next, stack_1->next));
  } else if ((stack_0 && !stack_1) || (!stack_0 && stack_1)) {
    return(false);
  } else {
    return(true);
  }
}
