#include <assert.h>
#include "../src/stack.h"
#include "../src/game.h"
#include "test_helper.h"

void test_valid_move_from_stock_to_stock() {
  struct stack *stock_0, *stock_1;

  stack_malloc(&stock_0);
  stack_malloc(&stock_1);
  stack_init(stock_0);
  stack_init(stock_1);
  card_set(stock_0->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  card_set(stock_1->card, KING, HEARTS, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  assert(!valid_move(stock_0, stock_0));
  assert(!valid_move(stock_0, stock_1));
  assert(!valid_move(stock_1, stock_0));
  assert(!valid_move(stock_1, stock_1));
  stack_free(stock_0);
  stack_free(stock_1);
}

void test_valid_move_from_stock_to_waste_pile() {
  struct stack *stock, *waste_pile;

  stack_malloc(&stock);
  stack_malloc(&waste_pile);
  stack_init(stock);
  stack_init(waste_pile);
  card_set(stock->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  card_set(waste_pile->card, KING, HEARTS, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  assert(valid_move(stock, waste_pile));
  stack_free(stock);
  stack_free(waste_pile);
}

void test_valid_move_from_stock_to_foundation_stacks() {
  struct stack *stock, *foundation_stacks[4];

  stack_malloc(&stock);
  stack_init(stock);
  card_set(stock->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    assert(!valid_move(stock, foundation_stacks[i]));
  }
  stack_free(stock);
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
}

void test_valid_move_from_stock_to_maneuvre_stacks() {
  struct stack *stock, *maneuvre_stacks[7];

  stack_malloc(&stock);
  stack_init(stock);
  card_set(stock->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    assert(!valid_move(stock, maneuvre_stacks[i]));
  }
  stack_free(stock);
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_waste_pile_to_stock() {
  struct stack *stock, *waste_pile;

  stack_malloc(&stock);
  stack_malloc(&waste_pile);
  stack_init(stock);
  stack_init(waste_pile);
  card_set(stock->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  card_set(waste_pile->card, KING, HEARTS, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  assert(!valid_move(waste_pile, stock));
  stack_free(stock);
  stack_free(waste_pile);
}

void test_valid_move_from_waste_pile_to_waste_pile() {
  struct stack *waste_pile_0, *waste_pile_1;

  stack_malloc(&waste_pile_0);
  stack_malloc(&waste_pile_1);
  stack_init(waste_pile_0);
  stack_init(waste_pile_1);
  card_set(waste_pile_0->card, ACE, SPADES, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  card_set(waste_pile_1->card, KING, HEARTS, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  assert(!valid_move(waste_pile_0, waste_pile_0));
  assert(!valid_move(waste_pile_0, waste_pile_1));
  assert(!valid_move(waste_pile_1, waste_pile_0));
  assert(!valid_move(waste_pile_1, waste_pile_1));
  stack_free(waste_pile_0);
  stack_free(waste_pile_1);
}

void test_valid_move_from_waste_pile_to_foundation_stacks() {
  struct stack *waste_pile, *foundation_stacks[4];

  stack_malloc(&waste_pile);
  stack_init(waste_pile);
  card_set(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    // TODO: fix error here
    assert(valid_move(waste_pile, foundation_stacks[i]));
  }
  stack_free(waste_pile);
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
}

void test_valid_move_from_waste_pile_to_maneuvre_stacks() {
  struct stack *waste_pile, *maneuvre_stacks[7];

  stack_malloc(&waste_pile);
  stack_init(waste_pile);
  card_set(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    // TODO: fix error here
    assert(valid_move(waste_pile, maneuvre_stacks[i]));
  }
  stack_free(waste_pile);
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_stock() {
  struct stack *stock, *foundation_stacks[4];

  stack_malloc(&stock);
  stack_init(stock);
  card_set(stock->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    assert(!valid_move(foundation_stacks[i], stock));
  }
  stack_free(stock);
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_waste_pile() {
  struct stack *waste_pile, *foundation_stacks[4];

  stack_malloc(&waste_pile);
  stack_init(waste_pile);
  card_set(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    assert(!valid_move(foundation_stacks[i], waste_pile));
  }
  stack_free(waste_pile);
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_foundation_stacks() {
  struct stack *foundation_stacks[4];

  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        assert(!valid_move(foundation_stacks[i], foundation_stacks[j]));
      } else {
        // TODO: fix error here
        assert(valid_move(foundation_stacks[i], foundation_stacks[j]));
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
}

void test_valid_move_from_foundation_stack_to_maneuvre_stacks() {
  struct stack *foundation_stacks[4];
  struct stack *maneuvre_stacks[7];

  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 7; j++) {
      // TODO: fix error here
      assert(valid_move(foundation_stacks[i], maneuvre_stacks[j]));
    }
  }
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_stock() {
  struct stack *stock, *maneuvre_stacks[7];

  stack_malloc(&stock);
  stack_init(stock);
  card_set(stock->card, ACE, SPADES, EXPOSED, STOCK_BEGIN_Y, STOCK_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    assert(!valid_move(maneuvre_stacks[i], stock));
  }
  stack_free(stock);
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_waste_pile() {
  struct stack *waste_pile, *maneuvre_stacks[7];

  stack_malloc(&waste_pile);
  stack_init(waste_pile);
  card_set(waste_pile->card, ACE, SPADES, EXPOSED, WASTE_PILE_BEGIN_Y, WASTE_PILE_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    assert(!valid_move(maneuvre_stacks[i], waste_pile));
  }
  stack_free(waste_pile);
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_foundation_stacks() {
  struct stack *foundation_stacks[4];
  struct stack *maneuvre_stacks[7];

  for (int i = 0; i < 4; i++) {
    stack_malloc(&foundation_stacks[i]);
    stack_init(foundation_stacks[i]);
  }
  card_set(foundation_stacks[0]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_0_BEGIN_X);
  card_set(foundation_stacks[1]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_1_BEGIN_X);
  card_set(foundation_stacks[2]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_2_BEGIN_X);
  card_set(foundation_stacks[3]->card, ACE, SPADES, EXPOSED, FOUNDATION_BEGIN_Y, FOUNDATION_3_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      // TODO: fix error here
      assert(valid_move(maneuvre_stacks[i], foundation_stacks[j]));
    }
  }
  for (int i = 0; i < 4; i++) {
    stack_free(foundation_stacks[i]);
  }
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_valid_move_from_maneuvre_stack_to_maneuvre_stacks() {
  struct stack *maneuvre_stacks[7];

  for (int i = 0; i < 7; i++) {
    stack_malloc(&maneuvre_stacks[i]);
    stack_init(maneuvre_stacks[i]);
  }
  card_set(maneuvre_stacks[0]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(maneuvre_stacks[1]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);
  card_set(maneuvre_stacks[2]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_2_BEGIN_X);
  card_set(maneuvre_stacks[3]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_3_BEGIN_X);
  card_set(maneuvre_stacks[4]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_4_BEGIN_X);
  card_set(maneuvre_stacks[5]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_5_BEGIN_X);
  card_set(maneuvre_stacks[6]->card, ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_6_BEGIN_X);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (i == j) {
        assert(!valid_move(maneuvre_stacks[i], maneuvre_stacks[j]));
      } else {
        // TODO: fix error here
        assert(valid_move(maneuvre_stacks[i], maneuvre_stacks[j]));
      }
    }
  }
  for (int i = 0; i < 7; i++) {
    stack_free(maneuvre_stacks[i]);
  }
}

void test_move_card_from_stack_empty_stack_to_stack_empty_stack() {
  struct stack *origin, *destination,
               *new_origin, *new_destination,
               *origin_duplicate, *destination_duplicate;

  stack_malloc(&origin);
  stack_malloc(&destination);
  stack_init(origin);
  stack_init(destination);
  new_origin = origin;
  new_destination = destination;
  origin_duplicate = stack_dup(origin);
  destination_duplicate = stack_dup(destination);
  move_card(&new_origin, &new_destination);

  assert(origin == new_origin);
  assert(stacks_equal(origin, origin_duplicate));
  assert(destination == new_destination);
  assert(stacks_equal(destination, destination_duplicate));

  stack_free(origin);
  stack_free(destination);
}

void test_move_card_from_stack_empty_stack_to_non_stack_empty_stack() {
  struct stack *origin, *destination,
               *new_origin, *new_destination,
               *origin_duplicate, *destination_duplicate;
  struct card *card;

  card_malloc(&card);
  card_init(card);
  card_set(card, ACE, SPADES, EXPOSED, 0, 0);

  stack_malloc(&origin);
  stack_malloc(&destination);
  stack_init(origin);
  stack_init(destination);
  new_origin = origin;
  new_destination = destination;
  stack_push(&new_destination, card);
  origin_duplicate = stack_dup(origin);
  destination_duplicate = stack_dup(destination);
  move_card(&new_origin, &new_destination);

  assert(origin == new_origin);
  assert(stacks_equal(origin, origin_duplicate));
  assert(destination == new_destination);
  assert(stacks_equal(destination, destination_duplicate));

  stack_free(origin);
  stack_free(destination);
}

void test_move_card_from_non_stack_empty_stack_to_stack_empty_stack() {
  struct stack *origin, *destination;
  struct card *card[6];

  for (int i = 0; i < 6; i++) {
    card_malloc(&card[i]);
    card_init(card[i]);
    card_set(card[i], TWO + i, i % 5, i % 2, 99, 99);
  }

  stack_malloc(&origin);
  stack_malloc(&destination);
  stack_init(origin);
  stack_init(destination);
  for (int i = 0; i < 6; i++) {
    stack_push(&origin, card[i]);
  }
  move_card(&origin, &destination);

  assert(stack_length(origin) == 5);
  assert(stack_length(destination) == 1);
  assert(cards_equal(destination->card, card[5]));

  move_card(&origin, &destination);

  assert(stack_length(origin) == 4);
  assert(stack_length(destination) == 2);
  assert(cards_equal(destination->card, card[4]));

  move_card(&origin, &destination);

  assert(stack_length(origin) == 3);
  assert(stack_length(destination) == 3);
  assert(cards_equal(destination->card, card[3]));

  stack_free(origin);
  stack_free(destination);
}

void test_move_card_from_non_stack_empty_stack_to_non_stack_empty_stack() {
  struct stack *origin, *destination;
  struct card *card[6];

  for (int i = 0; i < 6; i++) {
    card_malloc(&card[i]);
    card_init(card[i]);
    card_set(card[i], TWO + i, i % 5, i % 2, 99, 99);
  }

  stack_malloc(&origin);
  stack_malloc(&destination);
  stack_init(origin);
  stack_init(destination);
  for (int i = 0; i < 3; i++) {
    stack_push(&origin, card[i]);
  }
  for (int i = 3; i < 6; i++) {
    stack_push(&destination, card[i]);
  }
  move_card(&origin, &destination);

  assert(stack_length(origin) == 2);
  assert(stack_length(destination) == 4);
  assert(cards_equal(destination->card, card[2]));
  assert(cards_equal(destination->next->card, card[5]));

  stack_free(origin);
  stack_free(destination);
}

void test_move_card_should_not_change_stack_empty_stack_coordinates() {
  struct stack *origin, *destination;
  struct card *card[2];

  card_malloc(&card[0]);
  card_malloc(&card[1]);
  card_init(card[0]);
  card_init(card[1]);
  card_set(card[0], ACE, SPADES, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_0_BEGIN_X);
  card_set(card[1], KING, HEARTS, EXPOSED, MANEUVRE_BEGIN_Y, MANEUVRE_1_BEGIN_X);

  stack_malloc(&origin);
  stack_malloc(&destination);
  stack_init(origin);
  stack_init(destination);
  stack_push(&origin, card[0]);
  stack_push(&destination, card[1]);
  move_card(&origin, &destination);

  assert(origin->card->frame->begin_y == MANEUVRE_BEGIN_Y);
  assert(origin->card->frame->begin_x == MANEUVRE_0_BEGIN_X);

  stack_free(origin);
  stack_free(destination);
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

  test_move_card_from_stack_empty_stack_to_stack_empty_stack();
  test_move_card_from_stack_empty_stack_to_non_stack_empty_stack();
  test_move_card_from_non_stack_empty_stack_to_stack_empty_stack();
  test_move_card_from_non_stack_empty_stack_to_non_stack_empty_stack();
  test_move_card_should_not_change_stack_empty_stack_coordinates();
}
