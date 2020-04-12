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
               rm(win, c, env_macro(XKCD_IMG));
               rm(win, c, env_macro(XKCD_HTML));
          } break;
          case 2: {
               rm(win, c, env_macro(BC_IMG));
               rm(win, c, env_macro(BC_HTML));
          } break;
          case 3: {
               rm(win, c, env_macro(GARFIELD_IMG));
               rm(win, c, env_macro(GARFIELD_HTML));
          } break;
          case 4: {
               rm(win, c, env_macro(FAR_SIDE_IMG));
               rm(win, c, env_macro(FAR_SIDE_HTML));
          } break;
          case 5: {
               rm(win, c, env_macro(DILBERT_IMG));
               rm(win, c, env_macro(DILBERT_HTML));
          } break;
          case 6: {
               rm(win, c, env_macro(FAMILY_CIRCUS_IMG));
               rm(win, c, env_macro(FAMILY_CIRCUS_HTML));
          } break;
          case 7: {
               rm(win, c, env_macro(BLONDIE_IMG));
               rm(win, c, env_macro(BLONDIE_HTML));
          } break;
          case 8: {
               rm(win, c, env_macro(BEETLE_IMG));
               rm(win, c, env_macro(BEETLE_HTML));
          } break;
          case 999: {
               for (int x = 1; x <= 8; x++)
                    rm_coms(win, c, x);
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
               for (int x = 1; x <= 8; x++)
                    get_coms(load_output, c, x);
          } break;
          }
}

void show_coms(int ccase)
{
     switch (ccase) {
     case 1: {
          show_img(env_macro(XKCD_IMG));
     } break;
     case 2: {
          show_img(env_macro(BC_IMG));
     } break;
     case 3: {
          show_img(env_macro(GARFIELD_IMG));
     } break;
     case 4: {
          show_img(env_macro(FAR_SIDE_IMG));
     } break;
     case 5: {
          show_img(env_macro(DILBERT_IMG));
     } break;
     case 6: {
          show_img(env_macro(FAMILY_CIRCUS_IMG));
     } break;
     case 7: {
          show_img(env_macro(BLONDIE_IMG));
     } break;
     case 8: {
          show_img(env_macro(BEETLE_IMG));
     } break;
     case 999: {
          for (int x = 0; x <= 8; x++)
               show_coms(x);
     } break;
     }
}

#endif /* LOGIC_C_ */
