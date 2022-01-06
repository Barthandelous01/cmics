#ifndef MENU_C_
#define MENU_C_

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"


void print_menu(WINDOW * menu_win, int highlight, char *items[], int n)
{
	/* Holder variables for positions of highlight and print iteration */
	int x, y;
	x = 2;
	y = 1;
	/* starts formatting */
	box(menu_win, 0, 0);
	/* iterate over values. When highlight is hit, change attributes */
	for (int i = 0; i < n; ++i) {
		if (highlight == i + 1) {
			wattron(menu_win, A_REVERSE);
			mvwprintw(menu_win, y, x, "%s", items[i]);
			wattroff(menu_win, A_REVERSE);
		} else {
			mvwprintw(menu_win, y, x, "%s", items[i]);
		}
		++y;
	}
	wrefresh(menu_win);
}

int get_menu(WINDOW *win, int *highlight, int n, char *items[])
{
	int c;
	print_menu(win, *highlight, items, n);
	while (1) {
		c = wgetch(win);
		switch(c) {
		case KEY_UP:
			if (*highlight == 1)
				*highlight = n;
			else
				--*highlight;
			break;
		case KEY_DOWN:
			if (*highlight == n)
				*highlight = 1;
			else
				++*highlight;
			break;
		case 97:
			return 999;
			break;
		case 10:
			return *highlight;
			break;
		default:
			break;

		}
		print_menu(win, *highlight, items, n);
	}
}

#endif				/* MENU_C_ */
