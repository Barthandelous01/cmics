#ifndef UTILS_C_
#define UTILS_C_

#include <ncurses.h>

#include "url.h"
#include "com_reg.h"
#include "constants.h"

void error_print(WINDOW *win, int placement, int is_error, char *good_message, char *bad_message) {
  if (is_error == 1)
    wattron(win, COLOR_PAIR(ERROR));
  else
    wattron(win, COLOR_PAIR(SUCCESS));

  mvwprintw(win, placement, 2, "%s", "::");

  if (is_error == 1) {
    wattroff(win, COLOR_PAIR(ERROR));
    mvwprintw(win, placement, 5, "%s", bad_message);
  } else {
    wattroff(win, COLOR_PAIR(SUCCESS));
    mvwprintw(win, placement, 5, "%s", good_message);
  }
  placement++;
  wrefresh(win);
}


int get_xkcd(WINDOW *win, int placement) {
  mvwprintw(win, placement, 2, "%s", "==> Downloading Site");
  placement++;
  wrefresh(win);
  int res = get_url("https://www.xkcd.com/", "/tmp/xkcdtemp.html");
  error_print(win, placement, res, "Site downloaded!", "Site not found");
  return 0;
}

#endif /* UTILS_C_ */
