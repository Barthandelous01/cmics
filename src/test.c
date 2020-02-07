#include <stdio.h>
#include "constants.h"
#include <string.h>
#include <stdlib.h>

int
main (void) {
  printf("%s", strcat(getenv("HOME"), XKCD_HTML));
}

