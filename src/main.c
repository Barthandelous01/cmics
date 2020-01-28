#include "menu.h"
#include "url.h"

int main(void){
  printf("%d", n_main_choices);

  /* ncurses init */
  initscr();
  clear();
  noecho();
  cbreak();
  raw();

  /* Calculate size of window */
  int y, x;
  getmaxyx(stdscr, y, x);

  /* Window variables */
  WINDOW *my_win;
  int c;
  int result = 0;
  int highlight_main = 1;
  my_win = newwin(y-1, 30, 0,0);
  keypad(my_win, TRUE);
  refresh(); /* Refresh stdscr */
  print_main_menu(my_win, highlight_main);

  /* Main event loop */
  while (1) {
    c = wgetch(my_win);
    mvwprintw(my_win, y, 0, "%c", c);
    switch (c) {
    case KEY_UP:
      if (highlight_main == 1)
        highlight_main = n_main_choices;
      else
        --highlight_main;
      break;
    case KEY_DOWN:
      if (highlight_main == n_main_choices)
        highlight_main = 1;
      else
        ++highlight_main;
      break;
    case 10:
      result = highlight_main;
      break;
    default:
      mvprintw(y, 0, "%d", c);
      refresh();
      break;
    };
    print_main_menu(my_win, highlight_main);
    if (result != 0)
      break;
  }


  /* Press any key to quit */
  clrtoeol();
  refresh();
  endwin();
  getch();
  return 0;
}
