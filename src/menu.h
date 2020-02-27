#ifndef MENU_H_
#define MENU_H_

#include "menu.c"

void print_menu(WINDOW * menu_win, int highlight, char *items[], int n);
int get_menu(WINDOW *win, int *highlight, int n, char *items[]);


#endif				/* MENU_H_ */
