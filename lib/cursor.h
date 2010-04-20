#ifndef CURSOR_H
#define CURSOR_H

#define CURSOR_STARTING_X 4
#define CURSOR_STARTING_Y 7

struct cursor {
  int x;
  int y;
};

enum movement { LEFT, DOWN, UP, RIGHT };

extern struct deck *deck;

void allocate_cursor(struct cursor **);
void initialize_cursor(struct cursor *);
void draw_cursor(struct cursor *);
void move_cursor(struct cursor *, enum movement);

#endif
