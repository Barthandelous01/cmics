#ifndef LOGIC_H_
#define LOGIC_H_

#include <sqlite3.h>
#include <ncurses.h>

void get_coms(WINDOW *load_output, int *c, int ccase, sqlite3 *db);
void rm_coms(WINDOW *win, int *c, int ccase);
void show_coms(int ccase);

#endif /* LOGIC_H_ */
