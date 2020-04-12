#include <string.h>
#include <stdio.h>

static int help()
{
     printf("%s", "\
I didn't recognize that. Available options are:\n\
\n\
    xkcd\n\
    bc\n\
    garfield\n\
    far_side\n\
    dilbert\n\
    family_circus\n\
    blondie\n\
    beetle_bailey\n");
     return 8888;
}

int com(char *name)
{
     if (strcmp(name, "xkcd") == 0)
          return 1;
     else if (strcmp(name, "bc") == 0)
          return 2;
     else if (strcmp(name, "garfield") == 0)
          return 3;
     else if (strcmp(name, "far_side") == 0)
          return 4;
     else if (strcmp(name, "dilbert") == 0)
          return 5;
     else if (strcmp(name, "family_circus") == 0)
          return 6;
     else if (strcmp(name, "blondie") == 0)
          return 7;
     else if (strcmp(name, "beetle_bailey") == 0)
          return 8;
     else
          return help();
}
