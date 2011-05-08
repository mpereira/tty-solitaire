#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "common.h"

char *tty_solitaire_error_message(int errno, char *file, int line) {
  char *message = malloc(sizeof(ERROR_MESSAGE_BUFFER_SIZE));
  snprintf(message,
           ERROR_MESSAGE_BUFFER_SIZE,
           "%s: %s (%s:%d)\n",
           program_name,
           strerror(errno),
           file,
           line - 1);
  return(message);
}
