#ifndef UTILS_H_
#define UTILS_H_

#include <ncurses.h>
#include <stdlib.h>

void win_print(WINDOW * win, int *placement, int x, char *message);
void error_print(WINDOW * win, int *placement, int is_error, char *good_message, char *bad_message);

#endif
