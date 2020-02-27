#ifndef LOGIC_C_
#define LOGIC_C_

#include <ncurses.h>

#include "constants.h"
#include "rm.h"

void rm_coms(WINDOW *win, int *c, int ccase)
{
     switch (ccase) {
          case 1: {
               rm(win, c, XKCD_IMG);
               rm(win, c, XKCD_HTML);
          } break;
          case 2: {
               rm(win, c, BC_IMG);
               rm(win, c, BC_HTML);
          } break;
          case 3: {
               rm(win, c, GARFIELD_IMG);
               rm(win, c, GARFIELD_HTML);
          } break;
          case 4: {
               rm(win, c, FAR_SIDE_IMG);
               rm(win, c, FAR_SIDE_HTML);
          } break;
          case 5: {
               rm(win, c, DILBERT_IMG);
               rm(win, c, DILBERT_HTML);
          } break;
          case 6: {
               rm(win, c, FAMILY_CIRCUS_IMG);
               rm(win, c, FAMILY_CIRCUS_HTML);
          } break;
          case 7: {
               rm(win, c, BLONDIE_IMG);
               rm(win, c, BLONDIE_HTML);
          }
          case 8: {
               rm(win, c, BEETLE_IMG);
               rm(win, c, BEETLE_HTML);
          } break;
          case 999: {
               rm(win, c, XKCD_IMG);
               rm(win, c, XKCD_HTML);
               rm(win, c, BC_IMG);
               rm(win, c, BC_HTML);
               rm(win, c, GARFIELD_IMG);
               rm(win, c, GARFIELD_HTML);
               rm(win, c, FAR_SIDE_IMG);
               rm(win, c, FAR_SIDE_HTML);
               rm(win, c, DILBERT_IMG);
               rm(win, c, DILBERT_HTML);
               rm(win, c, BLONDIE_IMG);
               rm(win, c, BLONDIE_HTML);
               rm(win, c, BEETLE_IMG);
               rm(win, c, BEETLE_HTML);
          } break;
          }

}

#endif /* LOGIC_C_ */
