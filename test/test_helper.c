#include "test_helper.h"

bool frames_equal(struct frame *frame_0, struct frame *frame_1) {
  if (frame_0 && frame_1) {
    return(frame_0->start_y == frame_1->start_y &&
           frame_0->start_x == frame_1->start_x);
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

struct frame *duplicate_frame(struct frame *frame) {
  struct frame *new_frame;

  allocate_frame(&new_frame);
  set_frame(new_frame, frame->start_y, frame->start_x);

  return(new_frame);
}

struct card *duplicate_card(struct card *card) {
  struct card *new_card;

  allocate_card(&new_card);
  set_card(new_card,
           card->value,
           card->suit,
           card->face,
           card->frame->start_y,
           card->frame->start_x);

  return(new_card);
}

struct stack *duplicate_stack(struct stack *stack) {
  struct stack *iterator = stack;
  struct stack *new_stack;

  allocate_stack(&new_stack);
  initialize_stack(new_stack);
  for (iterator = stack; iterator; iterator = iterator->next) {
    push(&new_stack, duplicate_card(iterator->card));
  }

  return(new_stack);
}
