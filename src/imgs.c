#ifndef IMGS_C_
#define IMGS_C_

#include <stdlib.h>
#include <string.h>

#include "constants.h"

void show_img(char *img)
{
     char cmd[200] = "/usr/local/bin/img ";
     strcat(cmd, " ");
     strcat(cmd, img);
     system(cmd);
}

#endif /* IMGS_C_ */
