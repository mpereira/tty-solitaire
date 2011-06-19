#ifndef TTY_SOLITAIRE_COMMON_H
#define TTY_SOLITAIRE_COMMON_H

#include <stdbool.h>

#define MIN_TERM_LINES 28
#define MIN_TERM_COLS 57
#define TTY_SOLITAIRE_BUFSIZ 100

#define SMALL_TERM_MSG "Please increase your terminal size to at least 57x28 or press q to quit."

extern const char *program_name;

void tty_solitaire_generic_error(int, char *, int);
bool term_size_ok();

#endif
