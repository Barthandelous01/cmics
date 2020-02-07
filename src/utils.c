#ifndef UTILS_C_
#define UTILS_C_

#include <ncurses.h>

#include "url.h"
#include "com_reg.c"
#include "constants.h"

void win_print(WINDOW *win, int *placement, int x, char *message) {
  mvwprintw(win, *placement, x, "%s", message);
  ++*placement;
  wrefresh(win);
}

void error_print(WINDOW *win, int *placement, int is_error, char *good_message, char *bad_message) {
  if (is_error == 1)
    wattron(win, COLOR_PAIR(ERROR));
  else
    wattron(win, COLOR_PAIR(SUCCESS));

  mvwprintw(win, *placement, 2, "%s", "::");

  if (is_error == 1) {
    wattroff(win, COLOR_PAIR(ERROR));
    mvwprintw(win, *placement, 5, "%s", bad_message);
  } else {
    wattroff(win, COLOR_PAIR(SUCCESS));
    mvwprintw(win, *placement, 5, "%s", good_message);
  }
  ++*placement;
  wrefresh(win);
}


#endif /* UTILS_C_ */
