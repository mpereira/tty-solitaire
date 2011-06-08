#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <getopt.h>
#include <errno.h>

#include "draw.h"
#include "game.h"
#include "keyboard.h"
#include "common.h"

const char *program_name;
struct game game;

void draw_greeting() {
  mvprintw(8, 26, "Welcome to tty-solitaire.");
  mvprintw(10, 23, "Move with the arrow keys or hjkl.");
  mvprintw(11, 19, "Use the space bar to mark and move cards.");
  mvprintw(12, 16, "After marking a card you can use m to increase ");
  mvprintw(13, 17, "and n to decrease the number of marked cards.");
  mvprintw(15, 19, "Press the space bar to play or q to quit.");
}

void usage() {
  printf("usage: %s [-v|--version] [-h|--help]\n", program_name);
  printf("  -v, --version  Show the version\n");
  printf("  -h, --help     Show this message\n");
}

void version() {
  FILE *version_file;
  char version_string[6];

  if (!(version_file = fopen("VERSION", "rb"))) {
    fprintf(stderr, tty_solitaire_error_message(errno, __FILE__, __LINE__));
    exit(errno);
  }
  fread(version_string, 1, 5, version_file);
  version_string[5] = '\0';
  printf("%s\n", version_string);
  fclose(version_file);
}

int main(int argc, char *argv[]) {
  int option;
  int option_index;
  int passes_through_deck = 3;
  static const struct option options[] = {
    {"help",    no_argument,       NULL, 'h'},
    {"version", no_argument,       NULL, 'v'},
    {"passes",  required_argument, NULL, 'p'}
  };

  program_name = argv[0];

  while ((option = getopt_long(argc, argv, "hvp:", options, &option_index)) != -1) {
    switch (option) {
    case 'v':
      version();
      exit(0);
    case 'p':
      passes_through_deck = atoi(optarg);
      break;
    case 'h':
    default:
      usage();
      exit(0);
    }
  }

  setlocale(LC_ALL, "");
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  curs_set(FALSE);
  set_escdelay(0);
  assume_default_colors(COLOR_WHITE, COLOR_GREEN);
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);

  draw_greeting();

  int key;
  do {
    switch (key = getch()) {
    case KEY_SPACEBAR:
      clear();
      refresh();
      game_init(&game, passes_through_deck);
      break;
    case 'q':
    case 'Q':
      endwin();
      return(0);
    }
  } while (key != KEY_SPACEBAR);

  do {
    if ((key = getch()) == 'q' || key == 'Q') {
      endwin();
      game_end();
      exit(0);
    } else {
      keyboard_event(key);
    }
  } while (!game_won());

  endwin();
  game_end();
  printf("You won.\n");

  return(0);
}
