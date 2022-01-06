#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define n_main_choices 3

#define ERROR 0
#define SUCCESS 1

#define n_comics 8

#define COMIC_URL_LEN ((1 << 7))
#define HOME_DIR_LEN ((1 << 8))
#define SQL_LOG_LEN ((1 << 9))

#define DIR                  "/.comics"

#define IMGS                 DIR"/imgs"
#define HTML                 DIR"/html"

#define DB                   DIR"/cmics.db"

#define XKCD_HTML            HTML"/xkcd.html"
#define XKCD_IMG             IMGS"/xkcd.png"

#define BC_HTML              HTML"/bc.html"
#define BC_IMG               IMGS"/bc.jpg"

#define GARFIELD_HTML        HTML"/garfield.html"
#define GARFIELD_IMG         IMGS"/garfield.gif"

#define FAR_SIDE_HTML        HTML"/far_side.html"
#define FAR_SIDE_IMG         IMGS"/far_side.jpg"

#define DILBERT_HTML         HTML"/dilbert.html"
#define DILBERT_IMG          IMGS"/dilbert.jpg"

#define FAMILY_CIRCUS_HTML   HTML"/family_circus.html"
#define FAMILY_CIRCUS_IMG    IMGS"/family_circus.gif"

#define BLONDIE_HTML         HTML"/blondie.html"
#define BLONDIE_IMG          IMGS"/blondie.gif"

#define BEETLE_HTML          HTML"/beetle.html"
#define BEETLE_IMG           IMGS"/beetle.gif"

#endif				/* CONSTANTS_H_ */
