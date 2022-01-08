#ifndef CURSES_H_
#define CURSES_H_

#include <ncurses.h>

void do_curses_main();
void print_menu(WINDOW * menu_win, int highlight, char *items[], int n);
int get_menu(WINDOW *win, int *highlight, int n, char *items[]);

#endif /* CURSES_H_ */
