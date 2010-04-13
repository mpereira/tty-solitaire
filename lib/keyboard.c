#include <stdio.h>
#include "keyboard.h"

int key_event() {
  int pressed_key;

  pressed_key = getchar();

  return(pressed_key);
}
