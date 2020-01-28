#include "menu.h"
#include "url.h"

int main(void){
  printf("%d", n_main_choices);

  /* ncurses init */
  initscr();
  clear();
  noecho();
  cbreak();

  /* Calculate size of window */
  int y, x;
  getmaxyx(stdscr, y, x);

  /* Window variables */
  WINDOW *my_win;
  int c;
  int highlight_main = 1;
  my_win = newwin(y-1, 30, 0,0);
  refresh(); /* Refresh stdscr */
  print_main_menu(my_win, highlight_main);

  /* Main event loop */
  while (1) {
    c = wgetch(my_win);
    mvwprintw(my_win, y, 0, "%c", c);
    wrefresh(my_win);
  }


  /* Press any key to quit */
  wgetch(my_win);
  clrtoeol();
  refresh();
  endwin();
  return 0;
}
