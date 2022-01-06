#ifndef COMS_H_
#define COMS_H_

#include <sqlite3.h>
#include <ncurses.h>

int get_xkcd(WINDOW * win, int *placement, sqlite3 *db);
int get_bc(WINDOW *win, int *placement, sqlite3 *db);
int get_far_side(WINDOW *win, int *placement, sqlite3 *db);
int get_garfield(WINDOW *win, int *placement, sqlite3 *db);
int get_dilbert(WINDOW *win, int *placement, sqlite3 *db);
int get_family_circus(WINDOW *win, int *placement, sqlite3 *db);
int get_beetle_bailey(WINDOW *win, int *placement, sqlite3 *db);
int get_blondie(WINDOW *win, int *placement, sqlite3 *db);

extern char *proxy;

#endif				/* COMS_H_ */
