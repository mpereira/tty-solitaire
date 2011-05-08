#include <assert.h>
#include "../lib/stack.h"
#include "../lib/game.h"
#include "test_helper.h"

void test_move_card_from_empty_stack_to_empty_stack() {
  struct stack *origin, *destination,
               *new_origin, *new_destination,
               *origin_duplicate, *destination_duplicate;

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  new_origin = origin;
  new_destination = destination;
  origin_duplicate = duplicate_stack(origin);
  destination_duplicate = duplicate_stack(destination);
  move_card(&new_origin, &new_destination);

  assert(origin == new_origin);
  assert(stacks_equal(origin, origin_duplicate));
  assert(destination == new_destination);
  assert(stacks_equal(destination, destination_duplicate));

  free_stack(origin);
  free_stack(destination);
}

void test_move_card_from_empty_stack_to_non_empty_stack() {
  struct stack *origin, *destination,
               *new_origin, *new_destination,
               *origin_duplicate, *destination_duplicate;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  new_origin = origin;
  new_destination = destination;
  push(&new_destination, card);
  origin_duplicate = duplicate_stack(origin);
  destination_duplicate = duplicate_stack(destination);
  move_card(&new_origin, &new_destination);

  assert(origin == new_origin);
  assert(stacks_equal(origin, origin_duplicate));
  assert(destination == new_destination);
  assert(stacks_equal(destination, destination_duplicate));

  free_stack(origin);
  free_stack(destination);
}

void test_move_card_from_non_empty_stack_to_empty_stack() {
  struct stack *origin, *destination;
  struct card *card;

  allocate_card(&card);
  initialize_card(card);
  set_card(card, ACE, SPADES, EXPOSED, 0, 0);

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  push(&origin, card);
  move_card(&origin, &destination);

  assert(empty(origin));
  assert(length(destination) == 1);
  assert(cards_equal(destination->card, card));

  free_stack(origin);
  free_stack(destination);
}

void test_move_card_from_non_empty_stack_to_non_empty_stack() {
  struct stack *origin, *destination;
  struct card *card[2];

  allocate_card(&card[0]);
  allocate_card(&card[1]);
  initialize_card(card[0]);
  initialize_card(card[1]);
  set_card(card[0], ACE, SPADES, EXPOSED, 99, 99);
  set_card(card[1], KING, HEARTS, EXPOSED, 99, 99);

  allocate_stack(&origin);
  allocate_stack(&destination);
  initialize_stack(origin);
  initialize_stack(destination);
  push(&origin, card[0]);
  push(&destination, card[1]);
  move_card(&origin, &destination);

  assert(empty(origin));
  assert(length(destination) == 2);
  assert(cards_equal(destination->card, card[0]));
  assert(cards_equal(destination->next->card, card[1]));

  free_stack(origin);
  free_stack(destination);
}

void test_valid_move_from_stock_to_stock() {
  struct stack *stock_0, *stock_1;

  allocate_stack(&stock_0);
  allocate_stack(&stock_1);
  initialize_stack(stock_0);
  initialize_stack(stock_1);
  set_card(stock_0->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  set_card(stock_1->card, KING, HEARTS, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  assert(!valid_move(stock_0, stock_0));
  assert(!valid_move(stock_0, stock_1));
  assert(!valid_move(stock_1, stock_0));
  assert(!valid_move(stock_1, stock_1));
  free_stack(stock_0);
  free_stack(stock_1);
}

void test_valid_move_from_stock_to_waste_pile() {
  struct stack *stock, *waste_pile;

  allocate_stack(&stock);
  allocate_stack(&waste_pile);
  initialize_stack(stock);
  initialize_stack(waste_pile);
  set_card(stock->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  set_card(waste_pile->card, KING, HEARTS, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  assert(valid_move(stock, waste_pile));
  free_stack(stock);
  free_stack(waste_pile);
}

void test_valid_move_from_stock_to_foundation_stacks() {
  struct stack *stock, *foundation_stacks[4];

  allocate_stack(&stock);
  initialize_stack(stock);
  set_card(stock->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 4; i++) {
    assert(!valid_move(stock, foundation_stacks[i]));
  }
  free_stack(stock);
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
}

void test_valid_move_from_stock_to_maneuvre_stacks() {
  struct stack *stock, *maneuvre_stacks[7];

  allocate_stack(&stock);
  initialize_stack(stock);
  set_card(stock->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 7; i++) {
    assert(!valid_move(stock, maneuvre_stacks[i]));
  }
  free_stack(stock);
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_waste_pile_to_stock() {
  struct stack *stock, *waste_pile;

  allocate_stack(&stock);
  allocate_stack(&waste_pile);
  initialize_stack(stock);
  initialize_stack(waste_pile);
  set_card(stock->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  set_card(waste_pile->card, KING, HEARTS, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  assert(!valid_move(waste_pile, stock));
  free_stack(stock);
  free_stack(waste_pile);
}

void test_valid_move_from_waste_pile_to_waste_pile() {
  struct stack *waste_pile_0, *waste_pile_1;

  allocate_stack(&waste_pile_0);
  allocate_stack(&waste_pile_1);
  initialize_stack(waste_pile_0);
  initialize_stack(waste_pile_1);
  set_card(waste_pile_0->card, ACE, SPADES, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  set_card(waste_pile_1->card, KING, HEARTS, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  assert(!valid_move(waste_pile_0, waste_pile_0));
  assert(!valid_move(waste_pile_0, waste_pile_1));
  assert(!valid_move(waste_pile_1, waste_pile_0));
  assert(!valid_move(waste_pile_1, waste_pile_1));
  free_stack(waste_pile_0);
  free_stack(waste_pile_1);
}

void test_valid_move_from_waste_pile_to_foundation_stacks() {
  struct stack *waste_pile, *foundation_stacks[4];

  allocate_stack(&waste_pile);
  initialize_stack(waste_pile);
  set_card(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 4; i++) {
    assert(valid_move(waste_pile, foundation_stacks[i]));
  }
  free_stack(waste_pile);
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
}

void test_valid_move_from_waste_pile_to_maneuvre_stacks() {
  struct stack *waste_pile, *maneuvre_stacks[7];

  allocate_stack(&waste_pile);
  initialize_stack(waste_pile);
  set_card(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 7; i++) {
    assert(valid_move(waste_pile, maneuvre_stacks[i]));
  }
  free_stack(waste_pile);
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_stock() {
  struct stack *stock, *foundation_stacks[4];

  allocate_stack(&stock);
  initialize_stack(stock);
  set_card(stock->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 4; i++) {
    assert(!valid_move(foundation_stacks[i], stock));
  }
  free_stack(stock);
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_waste_pile() {
  struct stack *waste_pile, *foundation_stacks[4];

  allocate_stack(&waste_pile);
  initialize_stack(waste_pile);
  set_card(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 4; i++) {
    assert(!valid_move(foundation_stacks[i], waste_pile));
  }
  free_stack(waste_pile);
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_foundation_stacks() {
  struct stack *foundation_stacks[4];

  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        assert(!valid_move(foundation_stacks[i], foundation_stacks[j]));
      } else {
        assert(valid_move(foundation_stacks[i], foundation_stacks[j]));
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_maneuvre_stacks() {
  struct stack *foundation_stacks[4];
  struct stack *maneuvre_stacks[7];

  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 7; j++) {
      assert(valid_move(foundation_stacks[i], maneuvre_stacks[j]));
    }
  }
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_stock() {
  struct stack *stock, *maneuvre_stacks[7];

  allocate_stack(&stock);
  initialize_stack(stock);
  set_card(stock->card, ACE, SPADES, EXPOSED, STOCK_STARTING_Y, STOCK_STARTING_X);
  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 7; i++) {
    assert(!valid_move(maneuvre_stacks[i], stock));
  }
  free_stack(stock);
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_waste_pile() {
  struct stack *waste_pile, *maneuvre_stacks[7];

  allocate_stack(&waste_pile);
  initialize_stack(waste_pile);
  set_card(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_STARTING_Y, WASTE_PILE_STARTING_X);
  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 7; i++) {
    assert(!valid_move(maneuvre_stacks[i], waste_pile));
  }
  free_stack(waste_pile);
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_foundation_stacks() {
  struct stack *foundation_stacks[4];
  struct stack *maneuvre_stacks[7];

  for (int i = 0; i < 4; i++) {
    allocate_stack(&foundation_stacks[i]);
    initialize_stack(foundation_stacks[i]);
  }
  set_card(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_0_STARTING_X);
  set_card(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_1_STARTING_X);
  set_card(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_2_STARTING_X);
  set_card(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_STARTING_Y, FOUNDATION_3_STARTING_X);
  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      assert(valid_move(maneuvre_stacks[i], foundation_stacks[j]));
    }
  }
  for (int i = 0; i < 4; i++) {
    free_stack(foundation_stacks[i]);
  }
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_maneuvre_stacks() {
  struct stack *maneuvre_stacks[7];

  for (int i = 0; i < 7; i++) {
    allocate_stack(&maneuvre_stacks[i]);
    initialize_stack(maneuvre_stacks[i]);
  }
  set_card(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_0_STARTING_X);
  set_card(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_1_STARTING_X);
  set_card(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_2_STARTING_X);
  set_card(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_3_STARTING_X);
  set_card(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_4_STARTING_X);
  set_card(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_5_STARTING_X);
  set_card(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_STARTING_Y, MANEUVRE_6_STARTING_X);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (i == j) {
        assert(!valid_move(maneuvre_stacks[i], maneuvre_stacks[j]));
      } else {
        assert(valid_move(maneuvre_stacks[i], maneuvre_stacks[j]));
      }
    }
  }
  for (int i = 0; i < 7; i++) {
    free_stack(maneuvre_stacks[i]);
  }
}

void test_game() {
  test_valid_move_from_stock_to_stock();
  test_valid_move_from_stock_to_waste_pile();
  test_valid_move_from_stock_to_foundation_stacks();
  test_valid_move_from_stock_to_maneuvre_stacks();
  test_valid_move_from_waste_pile_to_stock();
  test_valid_move_from_waste_pile_to_waste_pile();
  test_valid_move_from_waste_pile_to_foundation_stacks();
  test_valid_move_from_waste_pile_to_maneuvre_stacks();
  test_valid_move_from_foundation_stack_to_stock();
  test_valid_move_from_foundation_stack_to_waste_pile();
  test_valid_move_from_foundation_stack_to_foundation_stacks();
  test_valid_move_from_foundation_stack_to_maneuvre_stacks();
  test_valid_move_from_maneuvre_stack_to_stock();
  test_valid_move_from_maneuvre_stack_to_waste_pile();
  test_valid_move_from_maneuvre_stack_to_foundation_stacks();
  test_valid_move_from_maneuvre_stack_to_maneuvre_stacks();

  test_move_card_from_empty_stack_to_empty_stack();
  test_move_card_from_empty_stack_to_non_empty_stack();
  test_move_card_from_non_empty_stack_to_empty_stack();
  test_move_card_from_non_empty_stack_to_non_empty_stack();
}
