#ifndef MENU_H_
#define MENU_H_

#include "menu.c"

void print_main_menu(WINDOW * menu_win, int highlight);
void print_comic_menu(WINDOW * menu_win, int highlight);
int get_menu(WINDOW *win, int *highlight, void (*functionPtr)(WINDOW *, int), int n);


#endif				/* MENU_H_ */
