#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/* variable for menu items */
char *main_menu [ ] = {
                       "Remove old comics",
                       " Download comics ",
                       "   View comics   "
};
int n_main_choices = sizeof(main_menu) / sizeof(char *);

#define ERROR 0
#define SUCCESS 1

/* Variables for menu formatting */
char *comics [ ] = {
                    "     XKCD      ",
                    "      BC       ",
                    "    Garfield   ",
                    "  The Far Side ",
                    "    Dilbert    ",
                    " Family Circus ",
                    "    Blondie    ",
                    " Beetle Bailey "
};
/* size of types of comic */
int n_comics = sizeof(comics) / sizeof(char *);

#endif /* CONSTANTS_H_ */
