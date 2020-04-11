#ifndef DIRS_C_
#define DIRS_C_

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#include "constants.h"
#include "utils.h"

void check_dir(WINDOW *win, int *placement, char *dir)
{
     struct stat st = {0};
     if (stat(dir, &st) == -1) {
          win_print(win, placement, 2, "Directory not found, creating...");
          mkdir(dir, 0777);
     } else {
          win_print(win, placement, 2, "Directory found!");
     }
}

void check_dirs(WINDOW *win, int *placement)
{
     check_dir(win, placement, DIR);
     check_dir(win, placement, IMGS);
     check_dir(win, placement, HTML);
}


#endif /* DIRS_C_ */
