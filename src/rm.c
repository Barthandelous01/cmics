#ifndef RM_C_
#define RM_C_

#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "constants.h"
#include "utils.h"

void rm (WINDOW *win, int *placement, char *file)
{
     int res = remove(file);
     char filename[200] = "";
     char rest[200] = "";
     strcpy(filename, file);
     strcpy(rest, file);
     error_print(win, placement, res, strcat(filename, " was deleted!"), strcat(rest, " was not deleted."));
     free(file);
}

#endif /* RM_C_ */
