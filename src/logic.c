#ifndef LOGIC_C_
#define LOGIC_C_

#include <ncurses.h>

#include "constants.h"
#include "imgs.h"
#include "coms.h"
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

void get_coms(WINDOW *load_output, int *c, int ccase)
{
          switch (ccase) {
          case 1: {
               get_xkcd(load_output, c);
          } break;
          case 2: {
               get_bc(load_output, c);
          } break;
          case 3: {
               get_garfield(load_output, c);
          } break;
          case 4: {
               get_far_side(load_output, c);
          } break;
          case 5: {
               get_dilbert(load_output, c);
          } break;
          case 6: {
               get_family_circus(load_output, c);
          } break;
          case 7: {
               get_blondie(load_output, c);
          } break;
          case 8: {
               get_beetle_bailey(load_output, c);
          } break;
          case 999: {
               get_xkcd(load_output, c);
               get_bc(load_output, c);
               get_garfield(load_output, c);
               get_far_side(load_output, c);
               get_dilbert(load_output, c);
               get_family_circus(load_output, c);
               get_blondie(load_output, c);
               get_beetle_bailey(load_output, c);
          } break;
          }
}

void show_coms(int ccase)
{
     switch (ccase) {
     case 1: {
          show_img(XKCD_IMG);
     } break;
     case 2: {
          show_img(BC_IMG);
     } break;
     case 3: {
          show_img(GARFIELD_IMG);
     } break;
     case 4: {
          show_img(FAR_SIDE_IMG);
     } break;
     case 5: {
          show_img(DILBERT_IMG);
     } break;
     case 6: {
          show_img(FAMILY_CIRCUS_IMG);
     } break;
     case 7: {
          show_img(BLONDIE_IMG);
     } break;
     case 8: {
          show_img(BEETLE_IMG);
     } break;
     case 999: {
          show_img(XKCD_IMG);
          show_img(BC_IMG);
          show_img(GARFIELD_IMG);
          show_img(FAR_SIDE_IMG);
          show_img(DILBERT_IMG);
          show_img(FAMILY_CIRCUS_IMG);
          show_img(BLONDIE_IMG);
          show_img(BEETLE_IMG);
     } break;
     }
}

#endif /* LOGIC_C_ */
