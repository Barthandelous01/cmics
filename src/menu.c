#ifndef MENU_C_
#define MENU_C_

#include <ncurses.h>
#include <stdio.h>

/* Yes, this is global. Main menu variable. To be referenced by main. */
char *main_menu [ ] = {
                 "Remove old comics",
                 "Download comics",
                 "View comics"
};

/* Yes, this is global. Comic menu variable. To be referenced by main. */
char *comics [ ] = {
              "XKCD",
              "BC",
              "Garfield",
              "The Far Side",
              "Dilbert",
              "Family Circus",
              "Blondie",
              "Beetle Bailey"
};

/* Both global variables for main logic in main */
int n_main_choices = sizeof(main_menu) / sizeof(char *);
int n_comics = sizeof(comics) / sizeof(char *);

void print_main_menu(WINDOW *menu_win, int highlight) {
  int x, y;
  x = 2;
  y = 2;
  box(menu_win,0,0);
  for (int i = 0; i < n_main_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", main_menu[i]);
    } else {
      mvwprintw(menu_win, y, x, "%s", main_menu[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
}

#endif /* MENU_C_ */
