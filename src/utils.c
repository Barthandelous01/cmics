#ifndef UTILS_C_
#define UTILS_C_

#include <ncurses.h>

#include "url.h"
#include "com_reg.h"

void comic_switcher(int n, void (*fun)(int)) {
  switch (n) {
  case 1: { /* start 'XKCD' */
    (*fun)(n);
  } /* end 'XKCD' */
  case 2: { /* start 'BC' */
    (*fun)(n);
  } /* end 'BC' */
  case 3: { /* begin 'Garfield' */
    (*fun)(n);
  } /* end of 'Garfield' */
  case 4: { /* start 'The Far side' */
    (*fun)(n);
  } /* end 'The Far Side' */
  case 5: { /* start 'Dilbert' */
    (*fun)(n);
  } /* end 'Dilbert' */
  case 6: { /* start 'Family Circus' */
    (*fun)(n);
  } /* end 'Family Circus' */
  case 7: { /* start 'Blondie' */
    (*fun)(n);
  } /* end 'Blondie' */
  case 8: { /* start 'Beetle Bailey' */
    (*fun)(n);
  } /* end 'Beetle Bailey' */
    }
}

void error_print(WINDOW *win, int placement, int is_error, char *good_message, char *bad_message) {
  if (is_error == 1)
    wattron(win, COLOR_RED);
  else
    wattron(win, COLOR_GREEN);

  mvwprintw(win, placement, 2, "%s", "::");

  if (is_error == 1) {
    wattroff(win, COLOR_RED);
    mvwprintw(win, placement, 5, "%s", bad_message);
  } else {
    wattroff(win, COLOR_GREEN);
    mvwprintw(win, placement, 5, "%s", good_message);
  }
}


int get_xkcd(WINDOW *win, int placement) {
  mvwprintw(win, placement, 2, "%s", "==> Downloading Site");
  wrefresh(win);
  int res = get_url("https://www.xkcd.com/", "/var/xkcdtemp.html");
  error_print(win, placement, res, "Site downloaded!", "Site not found");
  return 0;
}


#endif /* UTILS_C_ */
