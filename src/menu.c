#ifndef MENU_C_
#define MENU_C_

#include <ncurses.h>
#include <stdio.h>

#include "constants.h"

void print_main_menu(WINDOW *menu_win, int highlight) {
  /* Holder variables for positions of highlight and print iteration */
  int x, y;
  x = 2;
  y = 1;
  /* starts formatting */
  box(menu_win,0,0);
  /* iterate over values. When highlight is hit, change attributes */
  for (int i = 0; i < n_main_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", main_menu[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, y, x, "%s", main_menu[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
}

void print_comic_menu (WINDOW *menu_win, int highlight) {

  /* Holder variables for positions of highlight and print iteration */
  int x, y;
  x = 2;
  y = 1;
  /* starts formatting */
  box(menu_win,0,0);
  /* iterate over values. When highlight is hit, change attributes */
  for (int i = 0; i < n_comics; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", comics[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, y, x, "%s", comics[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
}

#endif /* MENU_C_ */
