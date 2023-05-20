#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#include "common.h"
#include "game.h"
#include "keyboard.h"

#ifndef VERSION
#define VERSION "n/a"
#endif

const char *program_name;
struct game game;

void version();
void usage(const char *);
void draw_greeting();
void draw_you_won();

int main(int argc, char *argv[]) {
  int option;
  int option_index;
  int passes_through_deck = 3;
  static int four_color_deck;
  static int no_background_color;
  static const struct option options[] = {
      {"help", no_argument, NULL, 'h'},
      {"version", no_argument, NULL, 'v'},
      {"passes", required_argument, NULL, 'p'},
      {"four-color-deck", no_argument, &four_color_deck, 1},
      {"no-background-color", no_argument, &no_background_color, 1},
      {0, 0, 0, 0}};

  program_name = basename(argv[0]);

  while ((option = getopt_long(argc, argv, "hvp:", options, &option_index)) !=
         -1) {
    switch (option) {
    case 'v':
      version();
      exit(0);
    case 'p':
      passes_through_deck = atoi(optarg);
      break;
    case 'h':
    case '?':
      usage(program_name);
      exit(0);
    case 0:
      /* If this option set a "no_argument" flag, do nothing else now. */
      printf("options[option_index].name: %s\n", options[option_index].name);
      if (options[option_index].flag != 0)
        break;
    default:
      usage(program_name);
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
  if (no_background_color) {
    use_default_colors();
  } else {
    assume_default_colors(COLOR_WHITE, COLOR_GREEN);
  }
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_RED, COLOR_WHITE);
  init_pair(3, COLOR_GREEN, COLOR_WHITE);
  init_pair(4, COLOR_YELLOW, COLOR_WHITE);
  init_pair(5, COLOR_WHITE, COLOR_BLUE);
  init_pair(6, COLOR_WHITE, COLOR_GREEN);

  int key;

  while (!term_size_ok()) {
    clear();
    mvprintw(1, 1, SMALL_TERM_MSG);
    refresh();
    if ((key = getch()) == 'q' || key == 'Q') {
      endwin();
      return (0);
    }
  }

  clear();
  draw_greeting();
  refresh();

  for (;;) {
    if ((key = getch()) == 'q' || key == 'Q') {
      endwin();
      return (0);
    }
    if (term_size_ok()) {
      clear();
      draw_greeting();
      refresh();
      if (key == KEY_SPACEBAR) {
        clear();
        refresh();
        game_init(&game, passes_through_deck, four_color_deck);
        break;
      }
    } else if (key == KEY_RESIZE) {
      clear();
      mvprintw(1, 1, SMALL_TERM_MSG);
      refresh();
    }
  }

  do {
    keyboard_event(getch());
  } while (!game_won());

  clear();
  draw_you_won();
  refresh();
  getch();
  clear();

  endwin();
  game_end();

  return (0);
}

void draw_greeting() {
  mvprintw(8, 26, "Welcome to tty-solitaire.");
  mvprintw(10, 21, "Move with the arrow keys or <hjkl>.");
  mvprintw(12, 18, "Use the space bar to select and place cards.");
  mvprintw(14, 13, "After selecting a card you can use <m> to select more");
  mvprintw(15, 12, "and <n> to select fewer. Press <Shift+M> to select all.");
  mvprintw(17, 19, "Press the space bar to play or q to quit.");
}

void draw_you_won() {
  mvprintw(10, 8, "██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗██╗");
  mvprintw(11, 8, "╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║██║");
  mvprintw(12, 8, " ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║██║");
  mvprintw(13, 8, "  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║╚═╝");
  mvprintw(14, 8, "   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║██╗");
  mvprintw(15, 8, "   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝");
}

void usage(const char *program_name) {
  printf("usage: %s [OPTIONS]\n", program_name);
  printf("  -v, --version              Show version\n");
  printf("  -h, --help                 Show this message\n");
  printf("  -p, --passes               Number of passes through the deck  "
         "(default: 3)\n");
  printf("      --four-color-deck      Draw unique card suit colors       "
         "(default: false)\n");
  printf("      --no-background-color  Don't draw background color        "
         "(default: false)\n");
}

void version() { printf("%s\n", VERSION); }
