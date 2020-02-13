#ifndef CONSTANTS_H_
#define CONSTANTS_H_


/* variable for menu items */
char *main_menu[] = {
    "Remove old comics",
    " Download comics ",
    "   View comics   "
};

int n_main_choices = sizeof(main_menu) / sizeof(char *);

#define ERROR 0
#define SUCCESS 1

/* Variables for menu formatting */
char *comics[] = {
    "     XKCD      ",
    "      BC       ",
    "    Garfield   ",
    "  The Far Side ",
    "    Dilbert    ",
    " Family Circus "
};

/* size of types of comic */
int n_comics = sizeof(comics) / sizeof(char *);

#include "user_conf.h"

#define DIR HOME"/.comics"

#define IMGS DIR"/imgs"
#define HTML DIR"/html"

#define XKCD_HTML HTML"/xkcd.html"
#define XKCD_IMG IMGS"/xkcd.png"

#define BC_HTML HTML"/bc.html"
#define BC_IMG IMGS"/bc.jpg"

#define GARFIELD_HTML HTML"/garfield.html"
#define GARFIELD_IMG IMGS"/garfield.gif"

#define FAR_SIDE_HTML HTML"/far_side.html"
#define FAR_SIDE_IMG IMGS"/far_side.jpg"

#define DILBERT_HTML HTML"/dilbert.html"
#define DILBERT_IMG IMGS"/dilbert.jpg"

#define FAMILY_CIRCUS_HTML HTML"/family_circus.html"
#define FAMILY_CIRCUS_IMG IMGS"/family_circus.gif"

#endif				/* CONSTANTS_H_ */
