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
#include "coms.h"
#include "utils.h"

static void env_macro(char *macro, char *dest)
{
     strcpy(dest, getenv("HOME"));
     strcat(dest, macro);
}

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
     char temp[200];
     env_macro(DIR, temp);
     check_dir(win, placement, temp);
     env_macro(IMGS, temp);
     check_dir(win, placement, temp);
     env_macro(HTML, temp);
     check_dir(win, placement, temp);
}


#endif /* DIRS_C_ */
