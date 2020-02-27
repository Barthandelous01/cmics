#ifndef DIRS_H_
#define DIRS_H_

#include <ncurses.h>

#include "dirs.c"

void check_dir(WINDOW *win, int *placement, char *dir);
void check_dirs(WINDOW *win, int *placement);

#endif /* DIRS_H_ */
